#include "ChunkGrid.h"

#include "VoxelData.h"
#include "ChunkMeshBuilder.h"
#include "ChunkCollidersBuilder.h"
#include "LocalVoxelPositionCalculator.h"
#include "RayCaster.h"
#include "Materials.h"

#include "../utils/OuterSpiralIterator.h"

#include "../client/packets/ChunkRequestPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      const int GRID_H_WIDTH = 20;
      const int GRID_H_HEIGHT = 4;

      const int GRID_WIDTH = 2*GRID_H_WIDTH + 1;
      const int GRID_HEIGHT = 2*GRID_H_HEIGHT + 1;
      const int GRID_ARRAY_SIZE = GRID_WIDTH*GRID_WIDTH*GRID_HEIGHT;

      ChunkGrid::ChunkGrid(BlockBuilder* blockBuilder, gdp::SimulationDataManager* simulationDataManager, gdp::GridSpacePartition* terrainSimulationGrid, gdn::Client* client, gdc::GameDataManager* gameDataManager)
      {
        this->blockBuilder = blockBuilder;
        this->simulationDataManager = simulationDataManager;
        this->terrainSimulationGrid = terrainSimulationGrid;
        this->client = client;
        this->gameDataManager = gameDataManager;

        nodeIds = new int[GRID_ARRAY_SIZE];
        position = gdm::Vector3i(7, -2,7);
        clear();

        //nodes.setSize(2*GRID_ARRAY_SIZE);
      }

      ChunkGrid::ChunkGrid(const ChunkGrid& chunkGrid)
      {
        blockBuilder = chunkGrid.blockBuilder;
        simulationDataManager = chunkGrid.simulationDataManager;
        terrainSimulationGrid = chunkGrid.terrainSimulationGrid;
        client = chunkGrid.client;
        gameDataManager = chunkGrid.gameDataManager;
      }

      ChunkGrid& ChunkGrid::operator=(const ChunkGrid& chunkGrid)
      {
        blockBuilder = chunkGrid.blockBuilder;
        simulationDataManager = chunkGrid.simulationDataManager;
        terrainSimulationGrid = chunkGrid.terrainSimulationGrid;
        client = chunkGrid.client;
        gameDataManager = chunkGrid.gameDataManager;
        return *this;
      }

      ChunkGrid::~ChunkGrid()
      {
        for(int i=0;i<GRID_ARRAY_SIZE;i++)
        {
          int id = *(nodeIds + i);
          if(id != -1)
          {
            deleteNode(id);
          }
        }
        delete[] nodeIds;
      }

      void ChunkGrid::deleteChunkTrees(ArrayList<int>* trees)
      {
        for(int i=0;i<trees->size();i++)
        {
          int objectId = (*trees)[i];
          gameDataManager->getTreesManager()->deleteData(objectId);
        }
        trees->clear();
      }

      void ChunkGrid::deleteStructures(gdcv::ChunkStructures* structures)
      {
        deleteChunkTrees(&structures->trees);
      }

      void ChunkGrid::deleteChunkBoars(ArrayList<int>* boars)
      {
        for(int i=0;i<boars->size();i++)
        {
          int objectId = (*boars)[i];
          gameDataManager->getBoarsManager()->deleteData(objectId);
        }
        boars->clear();
      }

      void ChunkGrid::deleteChunkCreatures(gdcv::ChunkCreatures* creatures)
      {
        deleteChunkBoars(&creatures->boars);
      }

      int ChunkGrid::createNode()
      {
        int id = nodes.genSlot();
        ChunkGridNode& node = nodes[id];
        node.mesh = new ChunkMesh();

        node.updateMesh = true;
        node.updateCollider = true;

        return id;
      }

      void ChunkGrid::deleteNode(int id)
      {
        assert(id != -1);
        ChunkGridNode* node = &nodes[id];

        deleteStructures(&node->structures);
        deleteChunkCreatures(&node->creatures);

        unregisterChunkCollider(&node->collider);

        delete node->mesh;
        delete [] node->collider.structures;
        delete [] node->collider.simulationIds;

        node->mesh = NULL;
        node->collider.structures = NULL;
        node->collider.simulationIds = NULL;
        node->collider.size = 0;

        nodes.free(id);
      }

      int ChunkGrid::getIndex(int x, int y, int z) const
      {
        return (y*GRID_WIDTH + x)*GRID_WIDTH + z;
      }

      bool ChunkGrid::isValid(int x, int y, int z) const
      {
        if(x >= 0 && x < GRID_WIDTH)
        {
          if(y >= 0 && y < GRID_HEIGHT)
          {
            if(z >= 0 && z < GRID_WIDTH)
            {
              return true;
            }
          }
        }
        return false;
      }

      int ChunkGrid::getChunkIndex(int cx, int cy, int cz) const
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;
        if(isValid(x, y, z))
        {
          return *(nodeIds + getIndex(x, y, z));
        }
        return -1;
      }

      bool ChunkGrid::updateChunkMesh(ChunkGridNode* node, int x, int y, int z)
      {
        Chunk* xm;
        Chunk* xp;

        Chunk* ym;
        Chunk* yp;

        Chunk* zm;
        Chunk* zp;

        if(getBorderChunks(x, y, z, &xm, &xp, &ym, &yp, &zm, &zp))
        {
          int cx = position.x + x;
          int cy = position.y + y;
          int cz = position.z + z;

          ChunkMeshBuilder chunkMeshBuilder(blockBuilder, &node->chunk, node->mesh, cx*CHUNK_SIZE, cy*CHUNK_SIZE, cz*CHUNK_SIZE, xm, xp, ym, yp, zm, zp);
          chunkMeshBuilder.buildMesh();
          return true;
        }

        return false;
      }

      void ChunkGrid::registerChunkCollider(ChunkCollider* chunkCollider, int ax, int ay, int az)
      {
        for(int i=0;i<chunkCollider->size;i++)
        {
          int simulationId = simulationDataManager->createSimulationData(chunkCollider->structures + i);
          simulationDataManager->getSimulation()->addTerrain(ax, ay, az, simulationId);
          *(chunkCollider->simulationIds + i) = simulationId;
        }
      }

      void ChunkGrid::unregisterChunkCollider(ChunkCollider* chunkCollider)
      {
        for(int i=0;i<chunkCollider->size;i++)
        {
          simulationDataManager->deleteSimulationData(*(chunkCollider->simulationIds + i));
        }
      }

      void ChunkGrid::updateChunkCollider(ChunkGridNode* chunkGridNode, int cx, int cy, int cz)
      {
        ChunkCollider* collider = &chunkGridNode->collider;

        unregisterChunkCollider(collider);

        int ax = position.x + cx;
        int ay = position.y + cy;
        int az = position.z + cz;

        delete [] collider->structures;
        delete [] collider->simulationIds;
        collider->structures = NULL;
        collider->simulationIds = NULL;
        collider->size = 0;

        ChunkCollidersBuilder builder(&chunkGridNode->chunk, ax, ay, az);
        builder.buildColliders();
        builder.loadColliders(collider);

        registerChunkCollider(collider, ax, ay, az);
      }

      bool ChunkGrid::getBorderChunks(int x, int y, int z, Chunk** xm, Chunk** xp, Chunk** ym, Chunk** yp, Chunk** zm, Chunk** zp) const
      {
        *xm = NULL;
        *xp = NULL;

        *ym = NULL;
        *yp = NULL;

        *zm = NULL;
        *zp = NULL;

        bool loaded = true;

        if(x > 0)
        {
          *xm = getLocalChunk(x-1, y, z);
          if(*xm == NULL)
          {
            loaded = false;
          }
        }
        if(x < GRID_WIDTH - 1)
        {
          *xp = getLocalChunk(x+1, y, z);
          if(*xp == NULL)
          {
            loaded = false;
          }
        }

        if(y > 0)
        {
          *ym = getLocalChunk(x, y-1, z);
          if(*ym == NULL)
          {
            loaded = false;
          }
        }
        if(y < GRID_HEIGHT - 1)
        {
          *yp = getLocalChunk(x, y+1, z);
          if(*yp == NULL)
          {
            loaded = false;
          }
        }

        if(z > 0)
        {
          *zm = getLocalChunk(x, y, z-1);
          if(*zm == NULL)
          {
            loaded = false;
          }
        }
        if(z < GRID_WIDTH - 1)
        {
          *zp = getLocalChunk(x, y, z+1);
          if(*zp == NULL)
          {
            loaded = false;
          }
        }
        return loaded;
      }

      void ChunkGrid::clear()
      {
        for(int i=0;i<GRID_ARRAY_SIZE;i++)
        {
          *(nodeIds + i) = -1;
        }
      }

      int ChunkGrid::getSize() const
      {
        return GRID_ARRAY_SIZE;
      }

      int ChunkGrid::getHWidth() const
      {
        return GRID_H_WIDTH;
      }

      int ChunkGrid::getHHeight() const
      {
        return GRID_H_HEIGHT;
      }

      const gdm::Vector3i& ChunkGrid::getPosition() const
      {
        return position;
      }

      Chunk* ChunkGrid::getLocalChunk(int x, int y, int z) const
      {
        ChunkGridNode* node = getNode(x, y, z);
        if(node == NULL)
        {
          return NULL;
        }
        return &node->chunk;
      }

      ChunkGridNode* ChunkGrid::getNode(int x, int y, int z) const
      {
        assert(isValid(x, y, z));

        int index = getIndex(x, y, z);
        int id = *(nodeIds + index);
        if(id == -1)
        {
          return NULL;
        }
        return &nodes[id];
      }

      ChunkGridNode* ChunkGrid::getNode(int index) const
      {
        assert(index >= 0 && index < GRID_ARRAY_SIZE);

        int id = *(nodeIds + index);
        if(id == -1)
        {
          return NULL;
        }
        return &nodes[id];
      }

      ChunkGridNode* ChunkGrid::getNodeByAbsolute(int cx, int cy, int cz) const
      {
        int index = getChunkIndex(cx, cy, cz);
        if(index == -1)
        {
          return NULL;
        }

        return &nodes[index];
      }

      Chunk* ChunkGrid::getChunk(int cx, int cy, int cz) const
      {
        int index = getChunkIndex(cx, cy, cz);
        if(index == -1)
        {
          return NULL;
        }

        return &nodes[index].chunk;
      }

      Block* ChunkGrid::getBlock(int bx, int by, int bz) const
      {
        LocalVoxelPositionCalculator calculator(bx, by, bz);
        int cx;
        int cy;
        int cz;
        unsigned int cbx;
        unsigned int cby;
        unsigned int cbz;
        calculator.calculateChunkData(&cx, &cy, &cz, &cbx, &cby, &cbz);

        Chunk* chunk = getChunk(cx, cy, cz);
        if(chunk == NULL)
        {
          return NULL;
        }
        //std::cout << "getting block: " << cbx << " : " << cby << " : " << cbz << std::endl;
        return chunk->getBlock(cbx, cby, cbz);
      }

      void ChunkGrid::raycastToBlock(const gdm::Vector3& position, const gdm::Vector3& direction, BlockInfo* blockInfo) const
      {
        RayCaster rayCaster(position, direction);

        blockInfo->block = NULL;

        while(rayCaster.getIterrations() <= 10)
        {
          rayCaster.next();
          blockInfo->position = rayCaster.getPosition();
          blockInfo->block = getBlock(blockInfo->position.x, blockInfo->position.y, blockInfo->position.z);

          if(blockInfo->block == NULL)
          {
            return;
          }

          if(getMaterial((blockInfo->block)->getMaterialId())->isVisible())
          {
            return;
          }
        }
      }

      void ChunkGrid::raycastToBlockBefore(const gdm::Vector3& startPosition, const gdm::Vector3& direction, BlockInfo* blockInfo) const
      {
        blockInfo->block = NULL;

        RayCaster rayCaster(startPosition, direction);

        gdm::Vector3i nextPosition;
        Block* nextBlock = NULL;

        gdm::Vector3i position = rayCaster.getPosition();
        Block* block = getBlock(position.x, position.y, position.z);

        while(rayCaster.getIterrations() <= 10)
        {
          rayCaster.next();
          nextPosition = rayCaster.getPosition();
          nextBlock = getBlock(nextPosition.x, nextPosition.y, nextPosition.z);

          if(nextBlock == NULL)
          {
            blockInfo->block = NULL;
            return;
          }

          if(getMaterial(nextBlock->getMaterialId())->isVisible())
          {
            blockInfo->block = block;
            blockInfo->position = position;
            return;
          }

          position = nextPosition;
          block = nextBlock;
        }

        blockInfo->block = NULL;
        blockInfo->position = position;
      }

      void ChunkGrid::setPosition(const gdm::Vector3i& newPosition)
      {
        int* newNodeIds = new int[GRID_ARRAY_SIZE];
        gdm::Vector3i translation = newPosition - position;

        for(int x=0;x<GRID_WIDTH;x++)
        {
          for(int y=0;y<GRID_HEIGHT;y++)
          {
            for(int z=0;z<GRID_WIDTH;z++)
            {
              int oldx = x + translation.x;
              int oldy = y + translation.y;
              int oldz = z + translation.z;

              if(isValid(oldx, oldy, oldz))
              {
                *(newNodeIds + getIndex(x, y, z)) = *(nodeIds + getIndex(oldx, oldy, oldz));
                *(nodeIds + getIndex(oldx, oldy, oldz)) = -1;
              }
              else
              {
                *(newNodeIds + getIndex(x, y, z)) = -1;
              }
            }
          }
        }

        std::cout << "done copying..." << std::endl;

        /*
        for(int i=0;i<GRID_ARRAY_SIZE;i++)
        {
          int id = *(nodeIds + i);
          if(id != -1)
          {
            deleteNode(id);
          }
        }
        */

        for(int x=0;x<GRID_WIDTH;x++)
        {
          for(int y=0;y<GRID_HEIGHT;y++)
          {
            for(int z=0;z<GRID_WIDTH;z++)
            {
              int id = *(nodeIds + getIndex(x, y, z));

              if(id != -1)
              {
                int cx = x + position.x;
                int cy = y + position.y;
                int cz = z + position.z;
                deleteNode(id);
                //terrainSimulationGrid->clear(cx, cy, cz);
              }
            }
          }
        }

        std::cout << "done deleting nodes" << std::endl;

        delete [] nodeIds;
        nodeIds = newNodeIds;
        position = newPosition;
      }

      bool ChunkGrid::loadNextMeshInColumn(int x, int z)
      {
        for(int y=0;y<GRID_HEIGHT;y++)
        {
          assert(isValid(x, y, z));
          int index = getIndex(x, y, z);
          int nodeId = *(nodeIds + index);
          if(nodeId != -1)
          {
            ChunkGridNode* node = &nodes[nodeId];

            if(node->updateMesh)
            {
              if(updateChunkMesh(node, x, y, z))
              {
                node->updateMesh = false;
                return true;
              }
            }
          }
        }
        return false;
      }

      void ChunkGrid::loadNextMesh()
      {
        for(OuterSpiralIterator osi(GRID_H_WIDTH, GRID_H_WIDTH);osi.isValid();osi.next())
        {
          int x = osi.getX();
          int z = osi.getY();
          if(loadNextMeshInColumn(x, z))
          {
            return;
          }
        }
      }

      bool ChunkGrid::loadNextColliderInColumn(int x, int z)
      {
        for(int y=0;y<GRID_HEIGHT;y++)
        {
          assert(isValid(x, y, z));
          int index = getIndex(x, y, z);
          int nodeId = *(nodeIds + index);
          if(nodeId != -1)
          {
            ChunkGridNode* node = &nodes[nodeId];

            if(node->updateCollider)
            {
              updateChunkCollider(node, x, y, z);

              node->updateCollider = false;
              return true;
            }
          }
        }
        return false;
      }

      void ChunkGrid::loadNextCollider()
      {
        for(OuterSpiralIterator osi(GRID_H_WIDTH, GRID_H_WIDTH);osi.isValid();osi.next())
        {
          int x = osi.getX();
          int z = osi.getY();
          if(loadNextColliderInColumn(x, z))
          {
            return;
          }
        }
      }

      void ChunkGrid::requestNextChunksInColumn(int x, int z, int* amount)
      {
        for(int y=0;y<GRID_HEIGHT;y++)
        {
          assert(isValid(x, y, z));
          int index = getIndex(x, y, z);
          int nodeId = *(nodeIds + index);
          if(nodeId == -1)
          {
            client->sendPacket(gdcp::ChunkRequestPacket(x + position.x, y + position.y, z + position.z));
            (*amount)--;
            if(*amount <= 0)
            {
              return;
            }
          }
        }
      }

      void ChunkGrid::requestNextChunks()
      {
        int amount = 30;
        for(OuterSpiralIterator osi(GRID_H_WIDTH, GRID_H_WIDTH);osi.isValid();osi.next())
        {
          int x = osi.getX();
          int z = osi.getY();

          requestNextChunksInColumn(x, z, &amount);
          if(amount <= 0)
          {
            return;
          }
        }
      }

      void ChunkGrid::loadChunk(int cx, int cy, int cz, Chunk* chunk)
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;

        std::cout << "loading chunk at position: " << cx << " : " << cy << " : " << cz << std::endl;
        if(isValid(x, y, z))
        {
          std::cout << "CHUNK IS IN GRID! loading..." << std::endl;
          int index = getIndex(x, y, z);


          if(*(nodeIds + index) == -1)
          {
            *(nodeIds + index) = createNode();
          }

          ChunkGridNode* node = &nodes[*(nodeIds + index)];
          node->chunk = *chunk;
          node->updateMesh = true;
          node->updateCollider = true;
          std::cout << "CHUNK LOADED!" << std::endl;

          //updateChunkMesh(&node, x, y, z);

          //updateChunkCollider(&node, x, y, z);
        }
      }

      void ChunkGrid::deleteChunkTrees(int cx, int cy, int cz)
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;

        if(isValid(x, y, z))
        {
          int index = getIndex(x, y, z);


          if(*(nodeIds + index) == -1)
          {
            return;
          }

          ChunkGridNode* node = &nodes[*(nodeIds + index)];
          deleteChunkTrees(&node->structures.trees);
        }
      }

      void ChunkGrid::loadChunkTrees(int cx, int cy, int cz, ArrayList<int>* trees)
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;

        if(isValid(x, y, z))
        {
          int index = getIndex(x, y, z);

          if(*(nodeIds + index) == -1)
          {
            *(nodeIds + index) = createNode();
          }

          ChunkGridNode* node = &nodes[*(nodeIds + index)];

          node->structures.trees = *trees;
          std::cout << "CHUNK TREES LOADED!" << std::endl;
        }
      }

      void ChunkGrid::deleteChunkBoars(int cx, int cy, int cz)
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;

        if(isValid(x, y, z))
        {
          int index = getIndex(x, y, z);


          if(*(nodeIds + index) == -1)
          {
            return;
          }

          ChunkGridNode* node = &nodes[*(nodeIds + index)];
          deleteChunkBoars(&node->creatures.boars);
        }
      }

      void ChunkGrid::loadChunkBoars(int cx, int cy, int cz, ArrayList<int>* boars)
      {
        int x = cx - position.x;
        int y = cy - position.y;
        int z = cz - position.z;

        if(isValid(x, y, z))
        {
          int index = getIndex(x, y, z);

          if(*(nodeIds + index) == -1)
          {
            *(nodeIds + index) = createNode();
          }

          ChunkGridNode* node = &nodes[*(nodeIds + index)];

          node->creatures.boars = *boars;
          std::cout << "CHUNK BOARS LOADED!" << std::endl;
        }
      }

      void ChunkGrid::updateChunk(int cx, int cy, int cz)
      {
        ChunkGridNode* node = getNodeByAbsolute(cx, cy, cz);
        if(node != NULL)
        {
          node->updateMesh = true;
          node->updateCollider = true;
        }
      }

      void ChunkGrid::updateBlock(int bx, int by, int bz)
      {
        LocalVoxelPositionCalculator calculator(bx, by, bz);
        int cx;
        int cy;
        int cz;
        unsigned int cbx;
        unsigned int cby;
        unsigned int cbz;
        calculator.calculateChunkData(&cx, &cy, &cz, &cbx, &cby, &cbz);
        updateChunk(cx, cy, cz);

        if(cbx == 0)
        {
          updateChunk(cx - 1, cy, cz);
        }
        else if(cbx == CHUNK_SIZE - 1)
        {
          updateChunk(cx + 1, cy, cz);
        }

        if(cby == 0)
        {
          updateChunk(cx, cy - 1, cz);
        }
        else if(cby == CHUNK_SIZE - 1)
        {
          updateChunk(cx, cy + 1, cz);
        }

        if(cbz == 0)
        {
          updateChunk(cx, cy, cz - 1);
        }
        else if(cbz == CHUNK_SIZE - 1)
        {
          updateChunk(cx, cy, cz + 1);
        }
      }

      void ChunkGrid::removeBoar(int objectId, const gdm::Vector3i& chunkPosition)
      {
        gdm::Vector3i localPosition = chunkPosition - position;
        assert(isValid(localPosition.x, localPosition.y, localPosition.z));


        int index = getIndex(localPosition.x, localPosition.y, localPosition.z);


        int nodeId = *(nodeIds + index);
        assert(nodeId != -1);

        ChunkGridNode* node = &nodes[nodeId];
        node->creatures.boars.removeElement(objectId);
      }

      bool ChunkGrid::addBoar(int objectId, const gdm::Vector3i& chunkPosition)
      {
        gdm::Vector3i localPosition = chunkPosition - position;
        if(!isValid(localPosition.x, localPosition.y, localPosition.z))
        {
          return false;
        }
        int index = getIndex(localPosition.x, localPosition.y, localPosition.z);
        int nodeId = *(nodeIds + index);
        if(nodeId == -1)
        {
          return false;
        }

        ChunkGridNode* node = &nodes[nodeId];
        node->creatures.boars.add(objectId);
        return true;
      }
    }
  }
}
