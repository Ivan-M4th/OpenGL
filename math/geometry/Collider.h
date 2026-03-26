#ifndef GD_MATH_GEOMETRY_H
#define GD_MATH_GEOMETRY_H

#include "../../gddef.h"

#include "ConvexPolyhedron.h"

#include "../Vector3.h"
#include "../Transformation.h"

#include "../../physics/PhysicalInformation.h"


namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class Collider
        {
        private:
          const ConvexPolyhedron* shape;

        public:
          Transformation* transformation;
          Vector3* speed;
          gdp::PhysicalInformation* physicalInformation;

          Collider();
          Collider(const ConvexPolyhedron*, gdp::PhysicalInformation*);
          Collider(const ConvexPolyhedron*, Transformation*, Vector3*, gdp::PhysicalInformation*);
          Collider(const Collider&);
          Collider& operator=(const Collider&);

          void getBounds(float*, float*, float*, float*, float*, float*) const;
          const ConvexPolyhedron& getShape() const;
        };
      }
    }
  }
}

#endif
