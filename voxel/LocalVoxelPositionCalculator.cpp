#include "LocalVoxelPositionCalculator.h"

#include "VoxelData.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      LocalVoxelPositionCalculator::LocalVoxelPositionCalculator(int bx, int by, int bz)
      {
        this->bx = bx;
        this->by = by;
        this->bz = bz;
      }

      LocalVoxelPositionCalculator::LocalVoxelPositionCalculator(const LocalVoxelPositionCalculator& calculator)
      {
        bx = calculator.bx;
        by = calculator.by;
        bz = calculator.bz;
      }

      LocalVoxelPositionCalculator& LocalVoxelPositionCalculator::operator=(const LocalVoxelPositionCalculator& calculator)
      {
        bx = calculator.bx;
        by = calculator.by;
        bz = calculator.bz;
        return *this;
      }

      int LocalVoxelPositionCalculator::calculateChunkCoord(int x) const
      {
        if(x >= 0)
        {
          return x/CHUNK_SIZE;
        }
        return ((x + 1)/(int)CHUNK_SIZE) - 1;
      }

      void LocalVoxelPositionCalculator::calculateChunkCoords(int* cx, int* cy, int* cz) const
      {
        *cx = calculateChunkCoord(bx);
        *cy = calculateChunkCoord(by);
        *cz = calculateChunkCoord(bz);
      }

      unsigned int LocalVoxelPositionCalculator::calculateChunkBlockCoord(int cx, int x) const
      {
        int res = x - cx*CHUNK_SIZE;
        return res;
      }

      void LocalVoxelPositionCalculator::calculateChunkBlockCoords(int cx, int cy, int cz, unsigned int* cbx, unsigned int* cby, unsigned int* cbz) const
      {
        *cbx = calculateChunkBlockCoord(cx, bx);
        *cby = calculateChunkBlockCoord(cy, by);
        *cbz = calculateChunkBlockCoord(cz, bz);
      }

      void LocalVoxelPositionCalculator::calculateChunkData(int* cx, int* cy, int* cz, unsigned int* cbx, unsigned int* cby, unsigned int* cbz) const
      {
        calculateChunkCoords(cx, cy, cz);
        calculateChunkBlockCoords(*cx, *cy, *cz, cbx, cby, cbz);
      }
    }
  }
}
