#include "Animation.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {

        Animation::Animation()
        {
          duration = 0.0;
        }

        Animation::Animation(const ArrayList<JointAnimation>& jointAnimations)
        {
          this->jointAnimations = jointAnimations;
          calculateDuration();
        }

        Animation::Animation(const Animation& animation)
        {
          jointAnimations = animation.jointAnimations;
          duration = animation.duration;
        }

        Animation& Animation::operator=(const Animation& animation)
        {
          jointAnimations = animation.jointAnimations;
          duration = animation.duration;
          return *this;
        }

        void Animation::calculateDuration()
        {
          duration = 0.0;
          for(unsigned int i=0;i<jointAnimations.size();i++)
          {
            if(jointAnimations[i].getDuration() > duration)
            {
              duration = jointAnimations[i].getDuration();
            }
          }
        }

        float Animation::getDuration() const
        {
          return duration;
        }

        JointAnimation& Animation::getJointAnimation(unsigned int jointId) const
        {
          return jointAnimations[jointId];
        }

      }
    }
  }
}
