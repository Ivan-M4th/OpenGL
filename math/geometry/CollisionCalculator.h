#ifndef GD_MATH_GEOMETRY_COLLISIONCALCULATOR_H
#define GD_MATH_GEOMETRY_COLLISIONCALCULATOR_H

#include "../../gddef.h"

#include "SupportVertexCalculator.h"
#include "ConvexPolyhedron.h"
#include "Simplex.h"

#include "../Vector3.h"
#include "../Matrix4x4.h"

#include "../epa/Polytope.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class CollisionCalculator
        {
        private:
          SupportVertexCalculator supportCalculator;
          const Vector3* speed1;
          const Vector3* speed2;

        public:
          CollisionCalculator(const Matrix4x4*, const Matrix4x4*, const Matrix4x4*, const Matrix4x4*);
          CollisionCalculator(const Matrix4x4*, const Matrix4x4*, const Matrix4x4*, const Matrix4x4*, const Vector3*, const Vector3*);
          CollisionCalculator(const CollisionCalculator&);
          CollisionCalculator& operator=(const CollisionCalculator&);

          void setCalculatorRadius(float, float);

          void runGJK(const Vector3*, const ConvexPolyhedron&, const ConvexPolyhedron&, Simplex*, float*) const;
          void fillLine(const ConvexPolyhedron&, const ConvexPolyhedron&, Simplex*, bool*) const;
          void fillTriangle(const ConvexPolyhedron&, const ConvexPolyhedron&, Simplex*, bool*) const;
          void fillSimplex(const ConvexPolyhedron&, const ConvexPolyhedron&, Simplex*, bool*) const;
          void getCollisionInformation(const ConvexPolyhedron&, const ConvexPolyhedron&, const Simplex&, float*, Vector3*, Vector3*) const;
          void checkCollision(const ConvexPolyhedron&, const ConvexPolyhedron&, bool*, float*, Vector3*, Vector3*);
          void checkGJKRayCastCollision(const ConvexPolyhedron&, const ConvexPolyhedron&, float, bool*, float*, Vector3*) const;
        };
      }
    }
  }
}

#endif
