#include "Face.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        Face::Face()
        {
          flag = 0;
        }

        Face::Face(const HalfEdge& edge1, const HalfEdge& edge2, const HalfEdge& edge3)
        {
          *edges = edge1;
          *(edges + 1) = edge2;
          *(edges + 2) = edge3;
          flag = 1;
        }

        Face::Face(const Face& face)
        {
          for(unsigned int i=0;i<3;i++)
          {
            *(edges + i) = *(face.edges + i);
          }
          flag = face.flag;
        }

        Face& Face::operator=(const Face& face)
        {
          for(unsigned int i=0;i<3;i++)
          {
            *(edges + i) = *(face.edges + i);
          }
          flag = face.flag;
          return *this;
        }
      }
    }
  }
}
