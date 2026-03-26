#ifndef GD_MATH_GEOMETRY_SUPPORTVERTEXCALCULATOR_H
#define GD_MATH_GEOMETRY_SUPPORTVERTEXCALCULATOR_H

#include "ConvexPolyhedron.h"
#include "SupportVertex.h"

#include "../Vector3.h"
#include "../Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class SupportVertexCalculator
        {
        private:
          const Matrix4x4* transformation1;
          const Matrix4x4* iTransformation1;
          const Matrix4x4* transformation2;
          const Matrix4x4* iTransformation2;

        public:
          float radius1;
          float radius2;

          SupportVertexCalculator();
          SupportVertexCalculator(const Matrix4x4*, const Matrix4x4*, const Matrix4x4*, const Matrix4x4*);
          SupportVertexCalculator(const SupportVertexCalculator&);
          SupportVertexCalculator& operator=(const SupportVertexCalculator&);

          SupportVertex support(const Vector3&, const ConvexPolyhedron&, const ConvexPolyhedron&) const;
        };
      }
    }
  }
}

#endif
