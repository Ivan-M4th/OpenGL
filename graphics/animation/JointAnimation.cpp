#include "JointAnimation.h"

#include <iostream>
#include <cassert>

#include "../../math/Quaternion.h"
#include "../../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        JointAnimation::JointAnimation()
        {
          size = 0;
          timeStamps = NULL;
          poses = NULL;
        }

        JointAnimation::JointAnimation(const ArrayList<float>& timeStampsList, const ArrayList<gdm::Matrix4x4>& posesList)
        {
          size = timeStampsList.size();
          timeStamps = new float[size];
          poses = new JointPose[size];

          for(unsigned int i=0;i<size;i++)
          {
            *(timeStamps + i) = timeStampsList[i];
            *(poses + i) = posesList[i];
          }
        }

        JointAnimation::~JointAnimation()
        {
          delete [] timeStamps;
          delete [] poses;
        }

        JointAnimation::JointAnimation(const JointAnimation& jointAnimation)
        {
          size = jointAnimation.size;
          timeStamps = new float[size];
          poses = new JointPose[size];

          for(unsigned int i=0;i<size;i++)
          {
            *(timeStamps + i) = *(jointAnimation.timeStamps + i);
            *(poses + i) = *(jointAnimation.poses + i);
          }
        }

        JointAnimation& JointAnimation::operator=(const JointAnimation& jointAnimation)
        {
          delete [] timeStamps;
          delete [] poses;

          size = jointAnimation.size;
          timeStamps = new float[size];
          poses = new JointPose[size];
          for(unsigned int i=0;i<size;i++)
          {
            *(timeStamps + i) = *(jointAnimation.timeStamps + i);
            *(poses + i) = *(jointAnimation.poses + i);
          }
          return *this;
        }

        JointPose JointAnimation::getPoseAt(float animationTime)
        {
          float duration = getDuration();
          //std::cout << "duration: " << duration << std::endl;
          //std::cout << "size: " << size << std::endl;

          assert(size > 0);

          while(animationTime > duration)
          {
            animationTime-=duration;
          }

          JointPose p1;
          JointPose p2;
          float t;
          getPosesSurrounding(animationTime, &t, &p1, &p2);
          return p1.interpolate(t, p2);
        }

        void JointAnimation::getPosesSurrounding(float animationTime, float* t, JointPose* p1, JointPose* p2)
        {
          int i1 = 0;
          int i2 = 1;
          while(animationTime > *(timeStamps + i2))
          {
            i1 = i2;
            i2++;
          }

          float time1 = *(timeStamps + i1);
          float time2 = *(timeStamps + i2);
          *t = (animationTime - time1)/(time2 - time1);

          *p1 = *(poses + i1);
          *p2 = *(poses + i2);
        }

        float JointAnimation::getDuration() const
        {
          return *(timeStamps + size -1);
        }
      }
    }
  }
}
