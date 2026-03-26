#ifndef GD_MATH_GEOMETRY_AABB_H
#define GD_MATH_GEOMETRY_AABB_H

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class AABB
        {
        public:
          Vector3 minPos;
          Vector3 maxPos;

          AABB();
          AABB(const Vector3&, const Vector3&);
          AABB(const AABB&);
          AABB& operator=(const AABB&);

          bool isIntersecting(const AABB&) const;
          Vector3& getPosition();
          AABB group(const AABB&) const;
          float area() const;

          float getPenetrationX(const AABB&) const;
          float getPenetrationY(const AABB&) const;
          float getPenetrationZ(const AABB&) const;

          Vector3 getPenetration(const AABB&) const;
        };
      }
    }
  }
}

#endif
