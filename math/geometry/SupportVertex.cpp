#include "SupportVertex.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        SupportVertex::SupportVertex()
        {

        }

        SupportVertex::SupportVertex(const Vector3& position1, const Vector3& position2)
        {
          this->position1 = position1;
          this->position2 = position2;
        }

        SupportVertex::SupportVertex(const SupportVertex& supportVertex)
        {
          position1 = supportVertex.position1;
          position2 = supportVertex.position2;
        }

        SupportVertex& SupportVertex::operator=(const SupportVertex& supportVertex)
        {
          position1 = supportVertex.position1;
          position2 = supportVertex.position2;
          return *this;
        }

        Vector3 SupportVertex::getMDifference() const
        {
          return position1 - position2;
        }

        SupportVertex SupportVertex::operator+(const SupportVertex& supportVertex) const
        {
          return SupportVertex(position1 + supportVertex.position1, position2 + supportVertex.position2);
        }

        SupportVertex operator*(float x, const SupportVertex& supportVertex)
        {
          return SupportVertex(x*supportVertex.position1, x*supportVertex.position2);
        }
      }
    }
  }
}
