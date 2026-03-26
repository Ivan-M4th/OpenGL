#ifndef GD_UTILS_ANIMATIONREADER_H
#define GD_UTILS_ANIMATIONREADER_H

#include "../gddef.h"

#include "ArrayList.h"
#include "XMLNode.h"
#include "String.h"

#include "../graphics/animation/JointAnimation.h"
#include "../graphics/animation/Animation.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class AnimationReader
      {
      private:
        XMLNode* file;
        const ArrayList<String>* idNames;

        ArrayList<gdga::JointAnimation> jointAnimations;

        void getLocationId(const String&, bool*, unsigned int*) const;
        void readSource(const XMLNode&, const String&, String*) const;
        void readJointAnimation(const XMLNode&);
        void readJointAnimations(const XMLNode&);
      public:
        AnimationReader(XMLNode*, const ArrayList<String>*);

        gdga::Animation read();
      };
    }
  }
}

#endif
