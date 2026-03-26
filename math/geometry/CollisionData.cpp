#include "CollisionData.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        CollisionData::CollisionData(unsigned int id1, unsigned int id2, float time, const Vector3& normal, float penetration)
        {
          this->id1 = id1;
          this->id2 = id2;
          this->time = time;
          this->normal = normal;
          this->penetration = penetration;
        }

        CollisionData::CollisionData(const CollisionData& data)
        {
          id1 = data.id1;
          id2 = data.id2;
          time = data.time;
          normal = data.normal;
          penetration = data.penetration;
        }

        CollisionData& CollisionData::operator=(const CollisionData& data)
        {
          id1 = data.id1;
          id2 = data.id2;
          time = data.time;
          normal = data.normal;
          penetration = data.penetration;
          return *this;
        }

        unsigned int CollisionData::getID1() const
        {
          return id1;
        }

        unsigned int CollisionData::getID2() const
        {
          return id2;
        }

        float CollisionData::getTime() const
        {
          return time;
        }

        const Vector3& CollisionData::getNormal() const
        {
          return normal;
        }

        float CollisionData::getPenetration() const
        {
          return penetration;
        }
      }
    }
  }
}
