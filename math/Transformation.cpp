#include "Transformation.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Transformation::Transformation()
      {
        scale = Vector3(1.0, 1.0, 1.0);
      }

      Transformation::Transformation(const Transformation& transformation)
      {
        position = transformation.position;
        scale = transformation.scale;
        rotation = transformation.rotation;
        tmatrix = transformation.tmatrix;
        iltmatrix = transformation.iltmatrix;
        rotationMatrix = transformation.rotationMatrix;
        iRotationMatrix = transformation.iRotationMatrix;
      }

      Transformation& Transformation::operator=(const Transformation& transformation)
      {
        position = transformation.position;
        scale = transformation.scale;
        rotation = transformation.rotation;
        tmatrix = transformation.tmatrix;
        iltmatrix = transformation.iltmatrix;
        rotationMatrix = transformation.rotationMatrix;
        iRotationMatrix = transformation.iRotationMatrix;
        return *this;
      }

      void Transformation::calculate()
      {
        Matrix4x4 m;
        m.get(0,0) = scale.getX();
        m.get(1,1) = scale.getY();
        m.get(2,2) = scale.getZ();
        tmatrix = rotation.toMatrix4x4()*m;
        tmatrix.get(0,3) = position.getX();
        tmatrix.get(1,3) = position.getY();
        tmatrix.get(2,3) = position.getZ();

        m = Matrix4x4();
        m.get(0,0) = 1.0/scale.getX();
        m.get(1,1) = 1.0/scale.getY();
        m.get(2,2) = 1.0/scale.getZ();
        iltmatrix = m*rotation.conjugate().toMatrix4x4();

        rotationMatrix = rotation.toMatrix3x3();
        iRotationMatrix = rotation.conjugate().toMatrix3x3();
      }

      const Matrix4x4& Transformation::toMatrix4x4() const
      {
        return tmatrix;
      }

      const Matrix4x4& Transformation::getILinearTransformation() const
      {
        return iltmatrix;
      }

      const Matrix3x3& Transformation::getRotationMatrix() const
      {
        return rotationMatrix;
      }

      const Matrix3x3& Transformation::getIRotationMatrix() const
      {
        return iRotationMatrix;
      }
    }
  }
}
