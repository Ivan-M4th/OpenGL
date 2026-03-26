#ifndef GD_GRAPHICS_ANIMATION_ARMATURE_H
#define GD_GRAPHICS_ANIMATION_ARMATURE_H

#include "../../gddef.h"

#include "Joint.h"
#include "JointPose.h"
#include "../../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Armature
        {
        private:
          unsigned int jointAmount;
          Joint* rootJoint;

          void deleteData();
          void applyPose(Joint*, const JointPose*, const gdm::Matrix4x4&);
          void getPose(Joint*, gdm::Matrix4x4*) const;
        public:
          Armature();
          Armature(unsigned int, Joint*);
          Armature(const Armature&);
          Armature& operator=(const Armature&);
          ~Armature();

          unsigned int getJointAmount() const;

          void applyPose(const JointPose*, const gdm::Matrix4x4&);
          void applyPose(const JointPose*);
          void getPose(gdm::Matrix4x4*) const;

          Joint* getRoot();
          Joint* getJoint(unsigned int, Joint&);
          Joint* getJoint(unsigned int);

          Joint* getJoint(const gdu::String&, Joint*);
          Joint* getJoint(const gdu::String&);

          int getJointId(const gdu::String&);
        };
      }
    }
  }
}

#endif
