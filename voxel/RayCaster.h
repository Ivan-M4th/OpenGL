#ifndef GD_VOXEL_RAYCASTER_H
#define GD_VOXEL_RAYCASTER_H

#include "../gddef.h"

#include "../math/Vector3i.h"
#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class RayCaster
      {
      private:
        unsigned int count;

        gdm::Vector3i blockPosition;
        gdm::Vector3i toNextBlock;
        gdm::Vector3 stepsToNext;
        gdm::Vector3 steps;

        bool useX;
        bool useY;
        bool useZ;

        void calculateParameters(int, float, float, int*, float*, float*, bool*) const;

        void next(int, float, int*, float*) const;
        void next(int, float, int*, float*, int, float, int*, float*) const;
        void next(int, float, int*, float*, int, float, int*, float*, int, float, int*, float*) const;
      public:
        RayCaster(const gdm::Vector3&, const gdm::Vector3&);

        void next();

        const gdm::Vector3i& getPosition() const;
        unsigned int getIterrations() const;
      };
    }
  }
}

#endif
