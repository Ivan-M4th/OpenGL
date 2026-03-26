#ifndef GD_MATH_VECTOR3I_H
#define GD_MATH_VECTOR3I_H

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector3i
      {
      public:
        int x;
        int y;
        int z;

        Vector3i();
        Vector3i(int, int, int);
        Vector3i(const Vector3i&);
        Vector3i& operator=(const Vector3i&);
        int& getX();
        int& getY();
        int& getZ();

        bool operator==(const Vector3i&) const;
        bool operator!=(const Vector3i&) const;
        Vector3i operator+(const Vector3i&) const;
        Vector3i operator-(const Vector3i&) const;
      };

      Vector3i operator*(int, const Vector3i&);

      std::ostream& operator<<(std::ostream&, const Vector3i&);
    }
  }
}

#endif
