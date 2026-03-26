#ifndef GD_SERVER_OBJECTS_CHARACTER_H
#define GD_SERVER_OBJECTS_CHARACTER_H

#include "../../gddef.h"

#include "Animal.h"

#include "../../math/Vector3.h"

#include "../../utils/String.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
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
        };
      }
    }
  }
}

#endif
