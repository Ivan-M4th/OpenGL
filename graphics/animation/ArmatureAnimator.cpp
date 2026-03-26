#include "ArmatureAnimator.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        ArmatureAnimator::ArmatureAnimator()
        {
          time = 0.0;
          playedOnce = false;
          animation = NULL;
        }

        ArmatureAnimator::ArmatureAnimator(const ArrayList<unsigned int>& jointIds, Animation* animation)
        {
          this->jointIds = jointIds;
          this->animation = animation;
          time = 0.0;
          playedOnce = false;

          this->jointIds.trim();
        }

        ArmatureAnimator::ArmatureAnimator(unsigned int jointAmount, Animation* animation)
        {
          jointIds.setSize(jointAmount);
          jointIds.trim();
          for(unsigned int i=0;i<jointAmount;i++)
          {
            jointIds[i] = i;
          }
          this->animation = animation;
          playedOnce = false;
          time = 0.0;
        }

        ArmatureAnimator::ArmatureAnimator(const ArmatureAnimator& animator)
        {
          jointIds = animator.jointIds;
          time = animator.time;
          animation = animator.animation;
          playedOnce = animator.playedOnce;
        }

        ArmatureAnimator& ArmatureAnimator::operator=(const ArmatureAnimator& animator)
        {
          jointIds = animator.jointIds;
          time = animator.time;
          animation = animator.animation;
          playedOnce = animator.playedOnce;
          return *this;
        }

        void ArmatureAnimator::update(float timePassed)
        {
          time+=timePassed;
          while(time > animation->getDuration())
          {
            playedOnce = true;
            time-=animation->getDuration();
          }
        }

        void ArmatureAnimator::getPose(JointPose* poses)
        {
          //std::cout << "jointids: " << jointIds.size() << std::endl;
          for(unsigned int i=0;i<jointIds.size();i++)
          {
            unsigned int jointId = jointIds[i];
            //std::cout << "joint id: " << jointId << std::endl;
            *(poses + jointId) = animation->getJointAnimation(jointId).getPoseAt(time);
          }
        }

        Animation* ArmatureAnimator::getAnimation() const
        {
          return animation;
        }

        void ArmatureAnimator::setAnimation(Animation* animation)
        {
          if(this->animation != animation)
          {
            this->animation = animation;
            time = 0.0;
            playedOnce = false;
          }
        }

        void ArmatureAnimator::setJointIds(const ArrayList<unsigned int>& jointIds)
        {
          this->jointIds = jointIds;
          this->jointIds.trim();
        }

        bool ArmatureAnimator::hasPlayedOnce() const
        {
          return playedOnce;
        }
      }
    }
  }
}
