#ifndef GD_CLIENT_OBJECTS_CHARACTER_H
#define GD_CLIENT_OBJECTS_CHARACTER_H

#include "../../gddef.h"

#include "Animal.h"

#include "../../utils/String.h"
#include "../../math/Vector3.h"

#include "../../graphics/animation/Armature.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class Character : public Animal
        {
        protected:
          gdu::String name;

        public:
          Character();
          Character(const Character&);
          Character& operator=(const Character&);

          virtual void update(float);
        };
      }
    }
  }
}

#endif
