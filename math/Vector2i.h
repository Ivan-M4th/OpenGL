#ifndef GD_MATH_VECTOR2I_H
#define GD_MATH_VECTOR2I_H

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector2i
      {
      public:
        int x;
        int y;

        Vector2i();
        Vector2i(int, int);
        Vector2i(const Vector2i&);
        Vector2i& operator=(const Vector2i&);

        bool operator==(const Vector2i&) const;
        bool operator!=(const Vector2i&) const;
        Vector2i operator+(const Vector2i&) const;
        Vector2i operator-(const Vector2i&) const;
      };

      std::ostream& operator<<(std::ostream&, const Vector2i&);
    }
  }
}

#endif
