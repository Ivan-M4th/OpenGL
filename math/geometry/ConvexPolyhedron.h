#ifndef GD_MATH_GEOMETRY_CONVEXPOLYHEDRON_H
#define GD_MATH_GEOMETRY_CONVEXPOLYHEDRON_H

#include "AABB.h"

#include "../Vector3.h"
#include "../Matrix4x4.h"

#include "../../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class ConvexPolyhedron
        {
        private:
          float size;
          ArrayList<Vector3> positions;

          void calculateSize();
        public:
          ConvexPolyhedron();
          ConvexPolyhedron(const Vector3&, const Vector3&);
          ConvexPolyhedron(const ArrayList<Vector3>&);
          ConvexPolyhedron(const ConvexPolyhedron&);
          ConvexPolyhedron& operator=(const ConvexPolyhedron&);

          const Vector3& support(const Vector3&) const;
          Vector3 support(const Vector3&, const Matrix4x4*, const Matrix4x4*) const;
          AABB getAABB(const Matrix4x4*, const Matrix4x4*) const;
        };
      }
    }
  }
}

#endif
