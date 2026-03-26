#include "Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {

      Vector3i::Vector3i()
      {
        x = 0;
        y = 0;
        z = 0;
      }

      Vector3i::Vector3i(int x, int y, int z)
      {
        this->x = x;
        this->y = y;
        this->z = z;
      }

      Vector3i::Vector3i(const Vector3i& v)
      {
        x = v.x;
        y = v.y;
        z = v.z;
      }

      Vector3i& Vector3i::operator=(const Vector3i& v)
      {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
      }

      int& Vector3i::getX()
      {
        return x;
      }

      int& Vector3i::getY()
      {
        return y;
      }

      int& Vector3i::getZ()
      {
        return z;
      }

      bool Vector3i::operator==(const Vector3i& v) const
      {
        return x == v.x && y == v.y && z == v.z;
      }

      bool Vector3i::operator!=(const Vector3i& v) const
      {
        return !(*this == v);
      }

      Vector3i Vector3i::operator+(const Vector3i& v) const
      {
        return Vector3i(x + v.x, y + v.y, z + v.z);
      }

      Vector3i Vector3i::operator-(const Vector3i& v) const
      {
        return Vector3i(x - v.x, y - v.y, z - v.z);
      }

      Vector3i operator*(int x, const Vector3i& v)
      {
        return Vector3i(x*v.x, x*v.y, x*v.z);
      }

      std::ostream& operator<<(std::ostream& os, const Vector3i& v)
      {
        os << v.x << " : " << v.y << " : " << v.z;
        return os;
      }

    }
  }
}
