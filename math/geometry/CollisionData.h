#ifndef GD_MATH_GEOMETRY_COLLISIONDATA_H
#define GD_MATH_GEOMETRY_COLLISIONDATA_H

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class CollisionData
        {
        private:
          unsigned int id1;
          unsigned int id2;
          float time;
          Vector3 normal;
          float penetration;

        public:
          CollisionData(unsigned int, unsigned int, float, const Vector3&, float);
          CollisionData(const CollisionData&);
          CollisionData& operator=(const CollisionData&);

          unsigned int getID1() const;
          unsigned int getID2() const;
          float getTime() const;
          const Vector3& getNormal() const;
          float getPenetration() const;
        };
      }
    }
  }
}

#endif
