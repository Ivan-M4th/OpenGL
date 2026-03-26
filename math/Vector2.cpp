#include "Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Vector2::Vector2()
      {
        x = 0.0;
        y = 0.0;
      }

      Vector2::Vector2(float x, float y)
      {
        this->x = x;
        this->y = y;
      }

      Vector2::Vector2(const Vector2& v)
      {
        x = v.x;
        y = v.y;
      }

      Vector2& Vector2::operator=(const Vector2& v)
      {
        x = v.x;
        y = v.y;
        return *this;
      }

      Vector2 Vector2::operator+(const Vector2& v) const
      {
        return Vector2(x + v.x, y + v.y);
      }

      Vector2 Vector2::operator-(const Vector2& v) const
      {
        return Vector2(x - v.x, y - v.y);
      }

      Vector2 operator*(float x, const Vector2& v)
      {
        return Vector2(x*v.x, x*v.y);
      }
    }
  }
}
