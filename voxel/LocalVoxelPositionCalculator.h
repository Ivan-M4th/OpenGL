#ifndef GD_VOXEL_LOCALVOXELPOSITIONCALCULATOR_H
#define GD_VOXEL_LOCALVOXELPOSITIONCALCULATOR_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class LocalVoxelPositionCalculator
      {
      private:
        int bx;
        int by;
        int bz;
      public:
        LocalVoxelPositionCalculator(int, int, int);
        LocalVoxelPositionCalculator(const LocalVoxelPositionCalculator&);
        LocalVoxelPositionCalculator& operator=(const LocalVoxelPositionCalculator&);

        int calculateChunkCoord(int) const;
        void calculateChunkCoords(int*, int*, int*) const;

        unsigned int calculateChunkBlockCoord(int, int) const;
        void calculateChunkBlockCoords(int, int, int, unsigned int*, unsigned int*, unsigned int*) const;

        void calculateChunkData(int*, int*, int*, unsigned int*, unsigned int*, unsigned int*) const;
      };
    }
  }
}

#endif
