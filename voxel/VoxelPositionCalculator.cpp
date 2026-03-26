#include "VoxelPositionCalculator.h"

#include "Chunk.h"
#include "LocalVoxelPositionCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      VoxelPositionCalculator::VoxelPositionCalculator(const gdm::Vector3& v)
      {
        fx = v.getX();
        fy = v.getY();
        fz = v.getZ();
      }

      VoxelPositionCalculator::VoxelPositionCalculator(float fx, float fy, float fz)
      {
        this->fx = fx;
        this->fy = fy;
        this->fz = fz;
      }

      VoxelPositionCalculator::VoxelPositionCalculator(const VoxelPositionCalculator& calculator)
      {
        fx = calculator.fx;
        fy = calculator.fy;
        fz = calculator.fz;
      }

      VoxelPositionCalculator& VoxelPositionCalculator::operator=(const VoxelPositionCalculator& calculator)
      {
        fx = calculator.fx;
        fy = calculator.fy;
        fz = calculator.fz;
        return *this;
      }

      int VoxelPositionCalculator::calculateBlockCoord(float x) const
      {
        int bx = (int)x;
        if(x >= 0.0)
        {
          return bx;
        }
        return bx - 1;
      }

      void VoxelPositionCalculator::calculateBlockCoords(int* bx, int* by, int* bz) const
      {
        *bx = calculateBlockCoord(fx);
        *by = calculateBlockCoord(fy);
        *bz = calculateBlockCoord(fz);
      }

      void VoxelPositionCalculator::calculateChunkCoords(int* cx, int* cy, int* cz) const
      {
        int bx;
        int by;
        int bz;
        calculateBlockCoords(&bx, &by, &bz);
        LocalVoxelPositionCalculator calculator(bx, by, bz);
        calculator.calculateChunkCoords(cx, cy, cz);
      }
    }
  }
}
