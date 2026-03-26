#ifndef GD_SERVER_OBJECTS_CREATURE_H
#define GD_SERVER_OBJECTS_CREATURE_H

#include "../../gddef.h"

#include "../../physics/Object.h"

#include "../../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        class Creature : public gdp::Object
        {
        protected:
          int hp;
          int maxHp;

        public:
          Creature();
          Creature(const Creature&);
          Creature& operator=(const Creature&);

          int getHp() const;
          int getMaxHp() const;
        };
      }
    }
  }
}

#endif
