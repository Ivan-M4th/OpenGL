#ifndef GD_VOXEL_VOXELPOSITIONCALCULATOR_H
#define GD_VOXEL_VOXELPOSITIONCALCULATOR_H

#include "../gddef.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class VoxelPositionCalculator
      {
      private:
        float fx;
        float fy;
        float fz;
      public:
        VoxelPositionCalculator(const gdm::Vector3&);
        VoxelPositionCalculator(float, float, float);
        VoxelPositionCalculator(const VoxelPositionCalculator&);
        VoxelPositionCalculator& operator=(const VoxelPositionCalculator&);

        int calculateBlockCoord(float) const;
        void calculateBlockCoords(int*, int*, int*) const;

        void calculateChunkCoords(int*, int*, int*) const;
      };
    }
  }
}

#endif
