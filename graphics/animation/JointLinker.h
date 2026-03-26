#ifndef GD_GRAPHICS_ANIMATION_JOINTLINKER_H
#define GD_GRAPHICS_ANIMATION_JOINTLINKER_H

#include "../../gddef.h"

#include "Joint.h"
#include "../../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class JointLinker
        {
        public:
          Joint* joint;
          gdm::Matrix4x4 transformation;

          JointLinker();
          JointLinker(Joint*);
          JointLinker(const JointLinker&);
          JointLinker& operator=(const JointLinker&);

          gdm::Matrix4x4 getTransformation() const;
        };
      }
    }
  }
}

#endif
