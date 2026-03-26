#include "JointLinker.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        JointLinker::JointLinker()
        {
          joint = NULL;
        }

        JointLinker::JointLinker(Joint* joint)
        {
          this->joint = joint;
        }

        JointLinker::JointLinker(const JointLinker& linker)
        {
          joint = linker.joint;
          transformation = linker.transformation;
        }

        JointLinker& JointLinker::operator=(const JointLinker& linker)
        {
          joint = linker.joint;
          transformation = linker.transformation;
          return *this;
        }

        gdm::Matrix4x4 JointLinker::getTransformation() const
        {
          if(joint == NULL)
          {
            return transformation;
          }

          return joint->transformation*transformation;
        }
      }
    }
  }
}
