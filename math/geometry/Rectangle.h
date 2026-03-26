#ifndef GD_MATH_GEOMETRY_RECTANGLE_H
#define GD_MATH_GEOMETRY_RECTANGLE_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class Rectangle
        {
        public:
          float x;
          float y;

          float width;
          float height;

          Rectangle(float, float, float, float);
          Rectangle(const Rectangle&);
          Rectangle& operator=(const Rectangle&);

          bool isInside(float, float) const;
        };
      }
    }
  }
}

#endif
