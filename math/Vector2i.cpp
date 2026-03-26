#include "Vector2i.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Vector2i::Vector2i()
      {
        x = 0;
        y = 0;
      }

      Vector2i::Vector2i(int x, int y)
      {
        this->x = x;
        this->y = y;
      }

      Vector2i::Vector2i(const Vector2i& v)
      {
        x = v.x;
        y = v.y;
      }

      Vector2i& Vector2i::operator=(const Vector2i& v)
      {
        x = v.x;
        y = v.y;
        return *this;
      }

      bool Vector2i::operator==(const Vector2i& v) const
      {
        return x == v.x && y == v.y;
      }

      bool Vector2i::operator!=(const Vector2i& v) const
      {
        return !(*this == v);
      }

      Vector2i Vector2i::operator+(const Vector2i& v) const
      {
        return Vector2i(x + v.x, y + v.y);
      }

      Vector2i Vector2i::operator-(const Vector2i& v) const
      {
        return Vector2i(x - v.x, y - v.y);
      }

      std::ostream& operator<<(std::ostream& os, const Vector2i& v)
      {
        os << v.x << " : " << v.y;
        return os;
      }
    }
  }
}
