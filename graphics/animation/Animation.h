#ifndef GD_GRAPHICS_ANIMATION_ANIMATION_H
#define GD_GRAPHICS_ANIMATION_ANIMATION_H

#include "../../gddef.h"

#include "JointAnimation.h"

#include "../../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Animation
        {
        private:
          ArrayList<JointAnimation> jointAnimations;
          float duration;

          void calculateDuration();
        public:
          Animation();
          Animation(const ArrayList<JointAnimation>&);
          Animation(const Animation&);
          Animation& operator=(const Animation&);

          float getDuration() const;
          JointAnimation& getJointAnimation(unsigned int) const;
        };
      }
    }
  }
}

#endif
