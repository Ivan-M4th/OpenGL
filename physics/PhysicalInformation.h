#ifndef GD_PHYSICS_PHYSICALPROPERTIES_H
#define GD_PHYSICS_PHYSICALPROPERTIES_H

#include "../gddef.h"

#include "../math/Matrix3x3.h"
#include "../math/Transformation.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      extern const unsigned int FREE_OBJECT;
      extern const unsigned int CONTROLED_OBJECT;

      class PhysicalInformation
      {
      private:
        gdm::Matrix3x3 iLocalIntertiaMatrix;
        gdm::Matrix3x3 intertiaMatrix;
        gdm::Matrix3x3 iInteriaMatrix;

      public:
        bool moveable;
        bool onGround;
        float mass;
        unsigned int objectType;
        gdm::Matrix3x3 localIntertiaMatrix;
        bool useGravity;

        PhysicalInformation();
        PhysicalInformation(bool, float);
        PhysicalInformation(const PhysicalInformation&);
        PhysicalInformation& operator=(const PhysicalInformation&);

        const gdm::Matrix3x3 getILocalIntertiaMatrix() const;
        const gdm::Matrix3x3 getInertiaMatrix() const;
        const gdm::Matrix3x3 getIInertiaMatrix() const;

        void calculate(const gdm::Transformation&);
        void setBoxIntertiaMatrix(float, float, float);
      };
    }
  }
}

#endif
