#ifndef GD_MATH_EPA_HALFEDGE_H
#define GD_MATH_EPA_HALFEDGE_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        class HalfEdge
        {
        public:
          unsigned int positionIndex;
          unsigned int oppFaceIndex;
          unsigned int oppIndex;

          HalfEdge();
          HalfEdge(unsigned int, unsigned int, unsigned int);
          HalfEdge(const HalfEdge&);
          HalfEdge& operator=(const HalfEdge&);
        };
      }
    }
  }
}

#endif
