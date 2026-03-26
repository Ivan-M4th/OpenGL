#ifndef GD_VOXEL_CHUNK_H
#define GD_VOXEL_CHUNK_H

#include "../gddef.h"

#include "Block.h"
#include "TerrainStructure.h"
#include "VoxelData.h"

#include "../utils/ArrayList.h"

#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      struct ChunkCollider
      {
        TerrainStructure* structures = NULL;
        unsigned int* simulationIds = NULL;
        int size = 0;
      };

      class Chunk
      {
        friend class ChunkSet;

      private:
        mutable Block blocks[CHUNK_ARRAY_SIZE];
        ArrayList<TerrainStructure> structures;
        ArrayList<unsigned int> simulationsIds;

        unsigned int getIndex(unsigned int, unsigned int, unsigned int) const;
      public:
        Chunk();
        Chunk(const Chunk&);
        Chunk& operator=(const Chunk&);

        Block* getBlock(unsigned int, unsigned int, unsigned int) const;

        void addStructure(const TerrainStructure&);
        void clearStructures();
      };

      int blockCoordToChunkCoord(int);
      void blockCoordsToChunkCoords(int, int, int, int*, int*, int*);

      int blockCoordToLocalChunkBlockCoord(int, int); //chunk, block
      void blockCoordsToLocalChunkBlockCoords(int, int, int, int, int, int, int*, int*, int*); //chunk, block, out

      struct ChunkInfo
      {
        Chunk* chunk = NULL;
        gdm::Vector3i position;
      };
    }
  }
}

#endif
