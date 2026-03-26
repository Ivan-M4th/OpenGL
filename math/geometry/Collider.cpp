#include "Collider.h"

#include <cassert>

#include "SupportVertexCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        Collider::Collider()
        {
          shape = NULL;
          transformation = NULL;
          speed = NULL;
          physicalInformation = NULL;
        }

        Collider::Collider(const ConvexPolyhedron* shape, gdp::PhysicalInformation* physicalInformation)
        {
          this->shape = shape;
          this->physicalInformation = physicalInformation;
          transformation = NULL;
          speed = NULL;
        }

        Collider::Collider(const ConvexPolyhedron* shape, Transformation* transformation, Vector3* speed, gdp::PhysicalInformation* physicalInformation)
        {
          this->shape = shape;
          this->transformation = transformation;
          this->speed = speed;
          this->physicalInformation = physicalInformation;
        }

        Collider::Collider(const Collider& collider)
        {
          shape = collider.shape;
          transformation = collider.transformation;
          speed = collider.speed;
          physicalInformation = collider.physicalInformation;
        }

        Collider& Collider::operator=(const Collider& collider)
        {
          shape = collider.shape;
          transformation = collider.transformation;
          speed = collider.speed;
          physicalInformation = collider.physicalInformation;
          return *this;
        }

        const ConvexPolyhedron& Collider::getShape() const
        {
          return *shape;
        }

        void Collider::getBounds(float* minX, float* maxX, float* minY, float* maxY, float* minZ, float* maxZ) const
        {
          assert(shape != NULL);

          Vector3 e1(1.0, 0.0, 0.0);
          Vector3 e2(0.0, 1.0, 0.0);
          Vector3 e3(0.0, 0.0, 1.0);

          if(transformation == NULL)
          {
            *minX = e1.dot(shape->support(-e1));
            *maxX = e1.dot(shape->support(e1));

            *minY = e2.dot(shape->support(-e2));
            *maxY = e2.dot(shape->support(e2));

            *minZ = e3.dot(shape->support(-e3));
            *maxZ = e3.dot(shape->support(e3));
          }
          else
          {
            const Matrix4x4* tmatrix = &transformation->toMatrix4x4();
            const Matrix4x4* iLinearTransformation = &transformation->getILinearTransformation();

            *minX = e1.dot(shape->support(-e1, tmatrix, iLinearTransformation));
            *maxX = e1.dot(shape->support(e1, tmatrix, iLinearTransformation));

            *minY = e2.dot(shape->support(-e2, tmatrix, iLinearTransformation));
            *maxY = e2.dot(shape->support(e2, tmatrix, iLinearTransformation));

            *minZ = e3.dot(shape->support(-e3, tmatrix, iLinearTransformation));
            *maxZ = e3.dot(shape->support(e3, tmatrix, iLinearTransformation));
          }
        }
      }
    }
  }
}
