#ifndef GD_UTILS_AMATUREREADER_H
#define GD_UTILS_AMATUREREADER_H

#include "XMLNode.h"
#include "ArrayList.h"
#include "String.h"

#include "../graphics/animation/Joint.h"
#include "../graphics/animation/Armature.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class ArmatureReader
      {
      private:
        XMLNode* file;
        const ArrayList<String>* jointNames;

        ArrayList<String> idNames;

        unsigned int getId(const String&) const;
        gdga::Joint* readJoint(const XMLNode&);

      public:
        ArmatureReader();
        ArmatureReader(XMLNode*, const ArrayList<String>*);
        ArmatureReader(const ArmatureReader&);
        ArmatureReader& operator=(const ArmatureReader&);

        gdga::Armature read();
        const ArrayList<String>& getIdNames() const;
      };
    }
  }
}

#endif
