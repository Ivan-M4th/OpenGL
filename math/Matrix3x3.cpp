#include "Matrix3x3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Matrix3x3::Matrix3x3() : SquareMatrix(3)
      {

      }

      Vector3 Matrix3x3::operator*(const Vector3& v) const
      {
        float x = get(0,0)*v.getX() + get(0,1)*v.getY() + get(0,2)*v.getZ();
        float y = get(1,0)*v.getX() + get(1,1)*v.getY() + get(1,2)*v.getZ();
        float z = get(2,0)*v.getX() + get(2,1)*v.getY() + get(2,2)*v.getZ();
        return Vector3(x,y,z);
      }

      Matrix3x3 Matrix3x3::operator*(const Matrix3x3& matrix) const
      {
        Matrix3x3 prod;
        for(unsigned int i=0;i<prod.height;i++)
        {
          for(unsigned int j=0;j<prod.width;j++)
          {
            prod.get(i,j) = lineColumnProduct(i, j, matrix);
          }
        }
        return prod;
      }
    }
  }
}
