#ifndef GD_MATH_GEOMETRY_SUPPORTVERTEX_H
#define GD_MATH_GEOMETRY_SUPPORTVERTEX_H

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class SupportVertex
        {
        public:
          Vector3 position1;
          Vector3 position2;

          SupportVertex();
          SupportVertex(const Vector3&, const Vector3&);
          SupportVertex(const SupportVertex&);
          SupportVertex& operator=(const SupportVertex&);

          Vector3 getMDifference() const;
          SupportVertex operator+(const SupportVertex&) const;
        };

        SupportVertex operator*(float, const SupportVertex&);
      }
    }
  }
}

#endif
