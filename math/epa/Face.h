#ifndef GD_MATH_EPA_FACE_H
#define GD_MATH_EPA_FACE_H

#include "HalfEdge.h"

#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        class Face
        {
        public:
          unsigned int flag;
          HalfEdge edges[3];

          Face();
          Face(const HalfEdge&, const HalfEdge&, const HalfEdge&);
          Face(const Face&);
          Face& operator=(const Face&);
        };
      }
    }
  }
}

#endif
