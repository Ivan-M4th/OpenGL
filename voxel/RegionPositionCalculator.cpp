#include "RegionPositionCalculator.h"

#include "Region.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      RegionPositionCalculator::RegionPositionCalculator(int cx, int cy, int cz)
      {
        this->cx = cx;
        this->cy = cy;
        this->cz = cz;
      }

      RegionPositionCalculator::RegionPositionCalculator(const RegionPositionCalculator& calculator)
      {
        cx = calculator.cx;
        cy = calculator.cy;
        cz = calculator.cz;
      }

      RegionPositionCalculator& RegionPositionCalculator::operator=(const RegionPositionCalculator& calculator)
      {
        cx = calculator.cx;
        cy = calculator.cy;
        cz = calculator.cz;
        return *this;
      }

      int RegionPositionCalculator::calculateRegionCoord(int x) const
      {
        if(x >= 0)
        {
          return x/REGION_SIZE;
        }
        return ((x + 1)/REGION_SIZE) - 1;
      }

      void RegionPositionCalculator::calculateRegionPosition(int* rx, int* ry, int* rz) const
      {
        *rx = calculateRegionCoord(cx);
        *ry = calculateRegionCoord(cy);
        *rz = calculateRegionCoord(cz);
      }
    }
  }
}
