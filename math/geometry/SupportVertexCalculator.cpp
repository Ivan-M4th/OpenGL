#include "SupportVertexCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        SupportVertexCalculator::SupportVertexCalculator()
        {
          transformation1 = NULL;
          iTransformation1 = NULL;
          transformation2 = NULL;
          iTransformation2 = NULL;
        }

        SupportVertexCalculator::SupportVertexCalculator(const Matrix4x4* transformation1, const Matrix4x4* iTransformation1, const Matrix4x4* transformation2, const Matrix4x4* iTransformation2)
        {
          this->transformation1 = transformation1;
          this->iTransformation1 = iTransformation1;
          this->transformation2 = transformation2;
          this->iTransformation2 = iTransformation2;

          radius1 = 0.0;
          radius2 = 0.0;
        }

        SupportVertexCalculator::SupportVertexCalculator(const SupportVertexCalculator& calculator)
        {
          transformation1 = calculator.transformation1;
          iTransformation1 = calculator.iTransformation1;
          transformation2 = calculator.transformation2;
          iTransformation2 = calculator.iTransformation2;
          radius1 = calculator.radius1;
          radius2 = calculator.radius2;
        }

        SupportVertexCalculator& SupportVertexCalculator::operator=(const SupportVertexCalculator& calculator)
        {
          transformation1 = calculator.transformation1;
          iTransformation1 = calculator.iTransformation1;
          transformation2 = calculator.transformation2;
          iTransformation2 = calculator.iTransformation2;
          radius1 = calculator.radius1;
          radius2 = calculator.radius2;
          return *this;
        }

        SupportVertex SupportVertexCalculator::support(const Vector3& direction, const ConvexPolyhedron& shape1, const ConvexPolyhedron& shape2) const
        {
          Vector3 n;
          if(radius1 > 0.0 || radius2 > 0.0)
          {
            n = direction;
            n.normalize();
          }

          Vector3 direction1 = (*iTransformation1)*direction;
          Vector3 direction2 = (*iTransformation2)*(-direction);
          Vector3 position1 = (*transformation1)*shape1.support(direction1) + radius1*n;
          Vector3 position2 = (*transformation2)*shape2.support(direction2) - radius2*n;

          return SupportVertex(position1, position2);
        }
      }
    }
  }
}
