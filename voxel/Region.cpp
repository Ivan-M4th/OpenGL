#include "Region.h"

#include <cassert>

#include "LocalVoxelPositionCalculator.h"
#include "VoxelPositionCalculator.h"
#include "ChunkCollidersBuilder.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      const int REGION_SIZE = 16;
      const int REGION_LIST_SIZE = REGION_SIZE*REGION_SIZE*REGION_SIZE;

      Region::Region()
      {
        nodes = NULL;
        nodeIds = new int[REGION_LIST_SIZE];

        for(int i=0;i<REGION_LIST_SIZE;i++)
        {
          *(nodeIds + i) = -1;
        }
      }

      Region::Region(gdu::MemoryArray<RegionNode>* nodes)
      {
        this->nodes = nodes;

        nodeIds = new int[REGION_LIST_SIZE];

        for(int i=0;i<REGION_LIST_SIZE;i++)
        {
          *(nodeIds + i) = -1;
        }
      }

      Region::Region(const Region& region)
      {
        nodes = region.nodes;

        nodeIds = new int[REGION_LIST_SIZE];

        for(int i=0;i<REGION_LIST_SIZE;i++)
        {
          *(nodeIds + i) = -1;
        }
      }

      Region& Region::operator=(const Region& region)
      {
        //clear();

        nodes = region.nodes;
        return *this;
      }

      Region::~Region()
      {
        deleteData();
      }

      void Region::deleteChunkTrees(gds::GameDataManager* gameDataManager, ArrayList<int>* trees)
      {
        for(int i=0;i<trees->size();i++)
        {
          gameDataManager->deleteTree((*trees)[i]);
        }
        trees->clear();
      }

      void Region::deleteChunkStructures(gds::GameDataManager* gameDataManager, gdsv::ChunkStructures* structures)
      {
        deleteChunkTrees(gameDataManager, &structures->trees);
      }

      void Region::deleteChunkBoars(gds::GameDataManager* gameDataManager, ArrayList<int>* boars)
      {
        for(int i=0;i<boars->size();i++)
        {
          gameDataManager->deleteBoar((*boars)[i]);
        }
        boars->clear();
      }

      void Region::deleteChunkCreatures(gds::GameDataManager* gameDataManager, gdsv::ChunkCreatures* creatures)
      {
        deleteChunkBoars(gameDataManager, &creatures->boars);
      }

      void Region::deleteChunk(gds::GameDataManager* gameDataManager, RegionNode* regionNode)
      {
        deleteChunkStructures(gameDataManager, &regionNode->structures);
        deleteChunkCreatures(gameDataManager, &regionNode->creatures);

        unregisterChunkCollider(gameDataManager->getSimulationDataManager(), &regionNode->collider);
        deleteChunkCollider(&regionNode->collider);
      }

      void Region::deleteChunks(gds::GameDataManager* gameDataManager)
      {
        assert(nodes != NULL);
        for(int i=0;i<REGION_LIST_SIZE;i++)
        {
          if(*(nodeIds + i) != -1)
          {
            int id = *(nodeIds + i);

            deleteChunk(gameDataManager, &(*nodes)[id]);

            nodes->free(id);
            *(nodeIds + i) = -1;
          }
        }
      }

      void Region::deleteData()
      {
        //clear();
        delete [] nodeIds;
      }

      int Region::getIndex(int x, int y, int z) const //ok
      {
        return x + REGION_SIZE*(y + REGION_SIZE*z);
      }

      bool Region::isValid(int x, int y, int z) const //ok
      {
        if(x >= 0 && x < REGION_SIZE)
        {
          if(y >= 0 && y < REGION_SIZE)
          {
            if(z >= 0 && z < REGION_SIZE)
            {
              return true;
            }
          }
        }
        return false;
      }

      RegionNode* Region::getNode(int x, int y, int z) const //ok
      {
        assert(isValid(x, y, z));

        int id = *(nodeIds + getIndex(x, y, z));
        if(id == -1)
        {
          return NULL;
        }
        assert(nodes != NULL);
        return &(*nodes)[id];
      }

      RegionNode* Region::genNode(int x, int y, int z) const
      {
        assert(isValid(x, y, z));
        int index = getIndex(x, y, z);
        assert(*(nodeIds + index) == -1);
        assert(nodes != NULL);
        *(nodeIds + index) = nodes->genSlot();
        return &(*nodes)[*(nodeIds + index)];
      }

      void unregisterChunkCollider(gdp::SimulationDataManager* simulationDataManager, ChunkCollider* collider)
      {
        for(int i=0;i<collider->size;i++)
        {
          simulationDataManager->deleteSimulationData(*(collider->simulationIds + i));
        }
      }

      void deleteChunkCollider(ChunkCollider* collider)
      {
        delete [] collider->structures;
        delete [] collider->simulationIds;
        collider->structures = NULL;
        collider->simulationIds = NULL;
        collider->size = 0;
      }

      void createChunkCollider(int cx, int cy, int cz, Chunk* chunk, ChunkCollider* collider)
      {
        ChunkCollidersBuilder builder(chunk, cx, cy, cz);
        builder.buildColliders();
        builder.loadColliders(collider);
      }

      void registerChunkCollider(gdp::SimulationDataManager* simulationDataManager, int cx, int cy, int cz, ChunkCollider* collider)
      {
        for(int i=0;i<collider->size;i++)
        {
          int simulationId = simulationDataManager->createSimulationData(collider->structures + i);
          simulationDataManager->getSimulation()->addTerrain(cx, cy, cz, simulationId);
          *(collider->simulationIds + i) = simulationId;
        }
      }

      int chunkCoordToRegionCoord(int x)
      {
        if(x >= 0)
        {
          return x/REGION_SIZE;
        }
        return ((x + 1)/REGION_SIZE) - 1;
      }

      void chunkCoordsToRegionCoords(int cx, int cy, int cz, int* rx, int* ry, int* rz)
      {
        *rx = chunkCoordToRegionCoord(cx);
        *ry = chunkCoordToRegionCoord(cy);
        *rz = chunkCoordToRegionCoord(cz);
      }

      int chunkCoordToLocalRegionChunkCoord(int rx, int cx)
      {
        return cx - rx*REGION_SIZE;
      }

      void chunkCoordsToLocalRegionChunkCoords(int rx, int ry, int rz, int cx, int cy, int cz, int* lcx, int* lcy, int* lcz)
      {
        *lcx = chunkCoordToLocalRegionChunkCoord(rx, cx);
        *lcy = chunkCoordToLocalRegionChunkCoord(ry, cy);
        *lcz = chunkCoordToLocalRegionChunkCoord(rz, cz);
      }
    }
  }
}
