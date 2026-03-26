#ifndef GD_MATH_TRANSFORMATION_H
#define GD_MATH_TRANSFORMATION_H

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Transformation
      {
      private:
        Matrix3x3 rotationMatrix;
        Matrix3x3 iRotationMatrix;
        Matrix4x4 tmatrix;
        Matrix4x4 iltmatrix;

      public:
        Vector3 position;
        Vector3 scale;
        Quaternion rotation;

        Transformation();
        Transformation(const Transformation&);
        Transformation& operator=(const Transformation&);

        void calculate();

        const Matrix4x4& toMatrix4x4() const;
        const Matrix4x4& getILinearTransformation() const;
        const Matrix3x3& getRotationMatrix() const;
        const Matrix3x3& getIRotationMatrix() const;
      };
    }
  }
}

#endif
