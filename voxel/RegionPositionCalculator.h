#ifndef GD_VOXEL_REGIONPOSITIONCALCULATOR_H
#define GD_VOXEL_REGIONPOSITIONCALCULATOR_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class RegionPositionCalculator
      {
      private:
        int cx;
        int cy;
        int cz;

        int calculateRegionCoord(int) const;
      public:
        RegionPositionCalculator(int, int, int);
        RegionPositionCalculator(const RegionPositionCalculator&);
        RegionPositionCalculator& operator=(const RegionPositionCalculator&);

        void calculateRegionPosition(int*, int*, int*) const;
      };
    }
  }
}

#endif
