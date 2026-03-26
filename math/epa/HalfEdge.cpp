#include "HalfEdge.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        HalfEdge::HalfEdge()
        {

        }

        HalfEdge::HalfEdge(unsigned int positionIndex, unsigned int oppFaceIndex, unsigned int oppIndex)
        {
          this->positionIndex = positionIndex;
          this->oppFaceIndex = oppFaceIndex;
          this->oppIndex = oppIndex;
        }

        HalfEdge::HalfEdge(const HalfEdge& edge)
        {
          positionIndex = edge.positionIndex;
          oppFaceIndex = edge.oppFaceIndex;
          oppIndex = edge.oppIndex;
        }

        HalfEdge& HalfEdge::operator=(const HalfEdge& edge)
        {
          positionIndex = edge.positionIndex;
          oppFaceIndex = edge.oppFaceIndex;
          oppIndex = edge.oppIndex;
          return *this;
        }
      }
    }
  }
}
