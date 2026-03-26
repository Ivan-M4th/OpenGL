#include "AABB.h"

#include <algorithm>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        AABB::AABB()
        {

        }

        AABB::AABB(const Vector3& position, const Vector3& size)
        {
          minPos = position;
          maxPos = position + size;
        }

        AABB::AABB(const AABB& box)
        {
          minPos = box.minPos;
          maxPos = box.maxPos;
        }

        AABB& AABB::operator=(const AABB& box)
        {
          minPos = box.minPos;
          maxPos = box.maxPos;
          return *this;
        }

        Vector3& AABB::getPosition()
        {
          return minPos;
        }

        AABB AABB::group(const AABB& aabb) const
        {
          AABB res;

          float minX = std::min(minPos.getX(), aabb.minPos.getX());
          float minY = std::min(minPos.getY(), aabb.minPos.getY());
          float minZ = std::min(minPos.getZ(), aabb.minPos.getZ());

          float maxX = std::max(maxPos.getX(), aabb.maxPos.getX());
          float maxY = std::max(maxPos.getY(), aabb.maxPos.getY());
          float maxZ = std::max(maxPos.getZ(), aabb.maxPos.getZ());

          res.minPos = Vector3(minX, minY, minZ);
          res.maxPos = Vector3(maxX, maxY, maxZ);
          return res;
        }

        float AABB::area() const
        {
          Vector3 difference = maxPos - minPos;
          return 2.0*(difference.getX()*difference.getY() + difference.getX()*difference.getZ() + difference.getY()*difference.getZ());
        }

        bool AABB::isIntersecting(const AABB& box) const
        {
          if(minPos.getX() < box.maxPos.getX() && maxPos.getX() > box.minPos.getX())
          {
            if(minPos.getY() < box.maxPos.getY() && maxPos.getY() > box.minPos.getY())
            {
              if(minPos.getZ() < box.maxPos.getZ() && maxPos.getZ() > box.minPos.getZ())
              {
                return true;
              }
            }
          }
          return false;
        }

        float AABB::getPenetrationX(const AABB& box) const
        {
          float x1 = maxPos.getX() - box.minPos.getX();
          float x2 = box.maxPos.getX() - minPos.getX();
          if(x1 <= x2)
          {
            return -x1;
          }
          return x2;
        }

        float AABB::getPenetrationY(const AABB& box) const
        {
          float y1 = maxPos.getY() - box.minPos.getY();
          float y2 = box.maxPos.getY() - minPos.getY();
          if(y1 <= y2)
          {
            return -y1;
          }
          return y2;
        }

        float AABB::getPenetrationZ(const AABB& box) const
        {
          float z1 = maxPos.getZ() - box.minPos.getZ();
          float z2 = box.maxPos.getZ() - minPos.getZ();
          if(z1 <= z2)
          {
            return -z1;
          }
          return z2;
        }

        Vector3 AABB::getPenetration(const AABB& box) const
        {
          float x = getPenetrationX(box);
          float y = getPenetrationY(box);
          float z = getPenetrationZ(box);

          float x2 = x*x;
          float y2 = y*y;
          float z2 = z*z;

          if(x2 < y2 && x2 < z2)
          {
            return Vector3(x, 0.0, 0.0);
          }
          else if(y2 < z2)
          {
            return Vector3(0.0, y, 0.0);
          }
          else
          {
            return Vector3(0.0, 0.0, z);
          }
        }
      }
    }
  }
}
