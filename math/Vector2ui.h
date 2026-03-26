#ifndef GD_MATH_VECTOR2UI_H
#define GD_MATH_VECTOR2UI_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector2ui
      {
      public:
        unsigned int x;
        unsigned int y;

        Vector2ui(unsigned int, unsigned int);
        Vector2ui(const Vector2ui&);
        Vector2ui& operator=(const Vector2ui&);
      };
    }
  }
}

#endif
