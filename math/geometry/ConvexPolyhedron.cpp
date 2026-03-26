#include "ConvexPolyhedron.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        ConvexPolyhedron::ConvexPolyhedron()
        {
          size = 0.0;
        }

        ConvexPolyhedron::ConvexPolyhedron(const Vector3& position, const Vector3& size)
        {
          float x = position.getX();
          float y = position.getY();
          float z = position.getZ();

          float sizeX = size.getX();
          float sizeY = size.getY();
          float sizeZ = size.getZ();

          positions.add(Vector3(x, y, z));
          positions.add(Vector3(x + sizeX, y, z));
          positions.add(Vector3(x, y + sizeY, z));
          positions.add(Vector3(x + sizeX, y + sizeY, z));

          positions.add(Vector3(x, y, z + sizeZ));
          positions.add(Vector3(x + sizeX, y, z + sizeZ));
          positions.add(Vector3(x, y + sizeY, z + sizeZ));
          positions.add(Vector3(x + sizeX, y + sizeY, z + sizeZ));

          calculateSize();
        }

        ConvexPolyhedron::ConvexPolyhedron(const ArrayList<Vector3>& positions)
        {
          this->positions = positions;
          this->positions.trim();
          calculateSize();
        }

        ConvexPolyhedron::ConvexPolyhedron(const ConvexPolyhedron& polyhedron)
        {
          positions = polyhedron.positions;
          size = polyhedron.size;
        }

        ConvexPolyhedron& ConvexPolyhedron::operator=(const ConvexPolyhedron& polyhedron)
        {
          positions = polyhedron.positions;
          size = polyhedron.size;
          return *this;
        }

        void ConvexPolyhedron::calculateSize()
        {
          size = 0.0;
          for(unsigned int i=0;i<positions.size();i++)
          {
            float length = positions[i].getLength();
            if(length > size)
            {
              size = length;
            }
          }
        }

        const Vector3& ConvexPolyhedron::support(const Vector3& direction) const
        {
          const Vector3* res = &positions[0];
          float dot = res->dot(direction);

          for(unsigned int i=1;i<positions.size();i++)
          {
            float testDot = positions[i].dot(direction);
            if(testDot > dot)
            {
              dot = testDot;
              res = &positions[i];
            }
          }
          return *res;
        }

        Vector3 ConvexPolyhedron::support(const Vector3& direction, const Matrix4x4* transformation, const Matrix4x4* iLinearTransformation) const
        {
          return (*transformation)*support((*iLinearTransformation)*direction);
        }

        AABB ConvexPolyhedron::getAABB(const Matrix4x4* transformation, const Matrix4x4* iLinearTransformation) const
        {
          AABB aabb;
          Vector3 e1(1.0, 0.0, 0.0);
          Vector3 e2(0.0, 1.0, 0.0);
          Vector3 e3(0.0, 0.0, 1.0);

          float minX = e1.dot(support(-e1, transformation, iLinearTransformation));
          float maxX = e1.dot(support(e1, transformation, iLinearTransformation));

          float minY = e2.dot(support(-e2, transformation, iLinearTransformation));
          float maxY = e2.dot(support(e2, transformation, iLinearTransformation));

          float minZ = e3.dot(support(-e3, transformation, iLinearTransformation));
          float maxZ = e3.dot(support(e3, transformation, iLinearTransformation));

          aabb.minPos = Vector3(minX, minY, minZ);
          aabb.maxPos = Vector3(maxX, maxY, maxZ);

          return aabb;
        }
      }
    }
  }
}
