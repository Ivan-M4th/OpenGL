#include "PhysicalInformation.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      const unsigned int FREE_OBJECT = 0;
      const unsigned int CONTROLED_OBJECT = 1;

      PhysicalInformation::PhysicalInformation()
      {
        moveable = true;
        onGround = false;
        mass = 1.0;
        objectType = FREE_OBJECT;
        useGravity = false;
      }

      PhysicalInformation::PhysicalInformation(bool moveable, float mass)
      {
        this->moveable = moveable;
        this->mass = mass;
        onGround = false;
        objectType = FREE_OBJECT;
        useGravity = false;
      }

      PhysicalInformation::PhysicalInformation(const PhysicalInformation& info)
      {
        moveable = info.moveable;
        onGround = info.onGround;
        mass = info.mass;
        objectType = info.objectType;
        useGravity = info.useGravity;
      }

      PhysicalInformation& PhysicalInformation::operator=(const PhysicalInformation& info)
      {
        moveable = info.moveable;
        onGround = info.onGround;
        mass = info.mass;
        objectType = info.objectType;
        useGravity = info.useGravity;
        return *this;
      }

      const gdm::Matrix3x3 PhysicalInformation::getILocalIntertiaMatrix() const
      {
        return iLocalIntertiaMatrix;
      }

      const gdm::Matrix3x3 PhysicalInformation::getInertiaMatrix() const
      {
        return intertiaMatrix;
      }

      const gdm::Matrix3x3 PhysicalInformation::getIInertiaMatrix() const
      {
        return iInteriaMatrix;
      }

      void PhysicalInformation::calculate(const gdm::Transformation& transformation)
      {
        intertiaMatrix = transformation.getRotationMatrix()*localIntertiaMatrix*transformation.getIRotationMatrix();
        iInteriaMatrix = transformation.getRotationMatrix()*iLocalIntertiaMatrix*transformation.getIRotationMatrix();
      }

      void PhysicalInformation::setBoxIntertiaMatrix(float x, float y, float z)
      {
        localIntertiaMatrix = gdm::Matrix3x3();
        float a = mass/12.0;
        localIntertiaMatrix.get(0,0) = a*(y*y + z*z);
        localIntertiaMatrix.get(1,1) = a*(x*x + z*z);
        localIntertiaMatrix.get(2,2) = a*(x*x + y*y);

        iLocalIntertiaMatrix = gdm::Matrix3x3();
        iLocalIntertiaMatrix.get(0,0) = 1.0/localIntertiaMatrix.get(0,0);
        iLocalIntertiaMatrix.get(1,1) = 1.0/localIntertiaMatrix.get(1,1);
        iLocalIntertiaMatrix.get(2,2) = 1.0/localIntertiaMatrix.get(2,2);
      }
    }
  }
}
