#ifndef GD_GRAPHICS_ANIMATION_ARMATUREANIMATOR_H
#define GD_GRAPHICS_ANIMATION_ARMATUREANIMATOR_H

#include "../../utils/ArrayList.h"

#include "Animation.h"
#include "JointPose.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class ArmatureAnimator
        {
        private:
          ArrayList<unsigned int> jointIds;
          float time;
          Animation* animation;
          bool playedOnce;

        public:
          ArmatureAnimator();
          ArmatureAnimator(const ArrayList<unsigned int>&, Animation*);
          ArmatureAnimator(unsigned int, Animation*);
          ArmatureAnimator(const ArmatureAnimator&);
          ArmatureAnimator& operator=(const ArmatureAnimator&);

          void update(float timePassed);
          void getPose(JointPose*);
          Animation* getAnimation() const;
          void setAnimation(Animation*);
          void setJointIds(const ArrayList<unsigned int>&);
          bool hasPlayedOnce() const;
        };
      }
    }
  }
}

#endif
