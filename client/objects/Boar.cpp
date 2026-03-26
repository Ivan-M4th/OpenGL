#include "Boar.h"

#include "../../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        Boar::Boar() : Animal()
        {
          collider = gdd::getConvexShape(gdd::BOAR_HITBOX_SHAPE);

          transformation.scale = gdm::Vector3(0.3, 0.3, 0.3);

          armature = *gdd::getArmature(gdd::BOAR_ARMATURE);
          gdga::Joint* rootJoint = armature.getJoint("Bone");
          ArrayList<unsigned int> jointIds;
          rootJoint->getChildrenIds(&jointIds);

          animator.setJointIds(jointIds);
          animator.setAnimation(gdd::getAnimation(gdd::BOAR_IDLE_ANIMATION));
        }

        Boar::Boar(const Boar& boar) : Animal(boar)
        {
          animator = boar.animator;
        }

        Boar& Boar::operator=(const Boar& boar)
        {
          Animal::operator=(boar);
          animator = boar.animator;
          return *this;
        }

        void Boar::update(float timePassed)
        {
          Animal::update(timePassed);

          animator.update(timePassed);
          gdga::JointPose pose[armature.getJointAmount()];
          animator.getPose(pose);
          armature.applyPose(pose);
        }
      }
    }
  }
}
