#ifndef GD_GRAPHICS_ANIMATION_JOINTANIMATION_H
#define GD_GRAPHICS_ANIMATION_JOINTANIMATION_H

#include "../../gddef.h"

#include "JointPose.h"
#include "../../math/Matrix4x4.h"
#include "../../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class JointAnimation
        {
        private:
          float* timeStamps;
          JointPose* poses;
          unsigned int size;
        public:
          JointAnimation();
          JointAnimation(const ArrayList<float>&, const ArrayList<gdm::Matrix4x4>&);
          ~JointAnimation();
          JointAnimation(const JointAnimation&);
          JointAnimation& operator=(const JointAnimation&);

          JointPose getPoseAt(float);
          void getPosesSurrounding(float, float*, JointPose*, JointPose*);
          float getDuration() const;
        };
      }
    }
  }
}

#endif
