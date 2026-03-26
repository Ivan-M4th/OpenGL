#include "Chunk.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      Chunk::Chunk()
      {
        for(unsigned int i=0;i<CHUNK_ARRAY_SIZE;i++)
        {
          (blocks + i)->setMaterial(1);
        }
        getBlock(1,15,1)->setMaterial(0);
        getBlock(1,15,2)->setMaterial(0);
        getBlock(2,15,1)->setMaterial(0);
        getBlock(2,15,2)->setMaterial(0);
      }

      Chunk::Chunk(const Chunk& chunk)
      {
        for(unsigned int i=0;i<CHUNK_ARRAY_SIZE;i++)
        {
          *(blocks + i) = *(chunk.blocks + i);
        }
      }

      Chunk& Chunk::operator=(const Chunk& chunk)
      {
        for(unsigned int i=0;i<CHUNK_ARRAY_SIZE;i++)
        {
          *(blocks + i) = *(chunk.blocks + i);
        }
        return *this;
      }

      unsigned int Chunk::getIndex(unsigned int x, unsigned int y, unsigned int z) const
      {
        return ((x*CHUNK_SIZE) + y)*CHUNK_SIZE + z;
      }

      Block* Chunk::getBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        assert(x < CHUNK_SIZE);
        assert(y < CHUNK_SIZE);
        assert(z < CHUNK_SIZE);
        return blocks + getIndex(x, y, z);
      }

      void Chunk::addStructure(const TerrainStructure& structure)
      {
        structures.add(structure);
      }

      void Chunk::clearStructures()
      {
        structures.clear();
      }

      int blockCoordToChunkCoord(int x)
      {
        if(x >= 0)
        {
          return x/CHUNK_SIZE;
        }
        return ((x + 1)/(int)CHUNK_SIZE) - 1;
      }

      void blockCoordsToChunkCoords(int bx, int by, int bz, int* cx, int* cy, int* cz)
      {
        *cx = blockCoordToChunkCoord(bx);
        *cy = blockCoordToChunkCoord(by);
        *cz = blockCoordToChunkCoord(bz);
      }

      int blockCoordToLocalChunkBlockCoord(int cx, int bx)
      {
        return bx - cx*(int)(CHUNK_SIZE);
      }

      void blockCoordsToLocalChunkBlockCoords(int cx, int cy, int cz, int bx, int by, int bz, int* lbx, int* lby, int* lbz)
      {
        *lbx = blockCoordToLocalChunkBlockCoord(cx, bx);
        *lby = blockCoordToLocalChunkBlockCoord(cy, by);
        *lbz = blockCoordToLocalChunkBlockCoord(cz, bz);
      }
    }
  }
}
