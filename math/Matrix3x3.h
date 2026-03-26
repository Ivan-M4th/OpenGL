#ifndef GD_MATH_MATRIX3X3_H
#define GD_MATH_MATRIX3X3_H

#include "SquareMatrix.h"
#include "Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Matrix3x3 : public SquareMatrix
      {
      public:
        Matrix3x3();

        Vector3 operator*(const Vector3&) const;
        Matrix3x3 operator*(const Matrix3x3&) const;
      };
    }
  }
}

#endif
