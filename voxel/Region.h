#ifndef GD_VOXEL_REGION_H
#define GD_VOXEL_REGION_H

#include "../gddef.h"

#include "Chunk.h"
#include "Block.h"

#include "../utils/Pointer.h"
#include "../utils/MemoryArray.h"

#include "../math/geometry/AABB.h"

#include "../server/GameDataManager.h"

#include "../server/voxel/ChunkStructures.h"
#include "../server/voxel/ChunkCreatures.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      extern const int REGION_SIZE;

      struct RegionNode
      {
        Chunk chunk;
        ChunkCollider collider;

        gdsv::ChunkStructures structures;
        gdsv::ChunkCreatures creatures;
      };

      class Region
      {
        friend class Terrain;

      private:
        gdu::MemoryArray<RegionNode>* nodes; //TO SET!!! (done)
        int* nodeIds;

        void deleteData();
        int getIndex(int, int, int) const;
        bool isValid(int, int, int) const;

      public:
        Region();
        Region(gdu::MemoryArray<RegionNode>*);
        Region(const Region&);
        Region& operator=(const Region&);
        ~Region();

        void deleteChunkTrees(gds::GameDataManager*, ArrayList<int>*);
        void deleteChunkStructures(gds::GameDataManager*, gdsv::ChunkStructures*);

        void deleteChunkBoars(gds::GameDataManager*, ArrayList<int>*);
        void deleteChunkCreatures(gds::GameDataManager*, gdsv::ChunkCreatures*);

        void deleteChunk(gds::GameDataManager*, RegionNode*);
        void deleteChunks(gds::GameDataManager*);

        RegionNode* getNode(int, int, int) const; //local coords
        RegionNode* genNode(int, int, int) const; //local coords
      };

      void unregisterChunkCollider(gdp::SimulationDataManager*, ChunkCollider*);
      void deleteChunkCollider(ChunkCollider*);
      void createChunkCollider(int, int, int, Chunk*, ChunkCollider*);
      void registerChunkCollider(gdp::SimulationDataManager*, int, int, int, ChunkCollider*);

      int chunkCoordToRegionCoord(int);
      void chunkCoordsToRegionCoords(int, int, int, int*, int*, int*);

      int chunkCoordToLocalRegionChunkCoord(int, int);
      void chunkCoordsToLocalRegionChunkCoords(int, int, int, int, int, int, int*, int*, int*); //region, chunk, out
    }
  }
}

#endif
