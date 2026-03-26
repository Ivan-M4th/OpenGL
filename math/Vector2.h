#ifndef GD_MATH_VECTOR2_H
#define GD_MATH_VECTOR2_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector2
      {
      public:
        float x;
        float y;

        Vector2();
        Vector2(float, float);
        Vector2(const Vector2&);
        Vector2& operator=(const Vector2&);

        Vector2 operator+(const Vector2&) const;
        Vector2 operator-(const Vector2&) const;
      };

      Vector2 operator*(float, const Vector2&);
    }
  }
}

#endif
