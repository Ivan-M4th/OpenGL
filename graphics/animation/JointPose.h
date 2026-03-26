#ifndef GD_GRAPHICS_ANIMATION_JOINTPOSE_H
#define GD_GRAPHICS_ANIMATION_JOINTPOSE_H

#include "../../gddef.h"

#include "../../math/Vector3.h"
#include "../../math/Quaternion.h"
#include "../../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class JointPose
        {
        private:
          bool defaultPose;

          gdm::Vector3 position;
          gdm::Vector3 scale;
          gdm::Quaternion rotation;
        public:
          JointPose();
          JointPose(const gdm::Vector3&, const gdm::Vector3&, const gdm::Quaternion&);
          JointPose(const gdm::Matrix4x4&);
          JointPose(const JointPose&);
          JointPose& operator=(const JointPose&);
          gdm::Matrix4x4 getTransformation() const;
          JointPose interpolate(float, const JointPose&) const;
          bool isDefaultPose() const;
        };
      }
    }
  }
}

#endif
