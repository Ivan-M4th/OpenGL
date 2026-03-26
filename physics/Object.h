#ifndef GD_PHYSICS_OBJECT_H
#define GD_PHYSICS_OBJECT_H

#include "../gddef.h"

#include "PhysicalInformation.h"

#include "../math/Vector3.h"
#include "../math/Transformation.h"
#include "../math/geometry/ConvexPolyhedron.h"

#include "../utils/MemoryArray.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class Object
      {
      public:
        gdm::Transformation transformation;
        gdm::Vector3 speed;
        gdm::Vector3 rotationSpeed;
        PhysicalInformation physicalInformation;
        const gdmg::ConvexPolyhedron* collider;

        Object();
        Object(const gdm::Vector3&);
        Object(const Object&);
        Object& operator=(const Object&);
        virtual ~Object();

        virtual void update(float);

        void calculateInformation();
        gdm::Vector3 getDirection(const gdm::Vector3&) const;
        float getRotationSpeedAngle() const;
        gdm::Vector3 getRotationDirection() const;
      };
    }
  }
}

#endif
