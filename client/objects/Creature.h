#ifndef GD_CLIENT_OBJECTS_CREATURE_H
#define GD_CLIENT_OBJECTS_CREATURE_H

#include "../../gddef.h"

#include "../../physics/Object.h"

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
        class Creature : public gdp::Object
        {
        protected:
          int hp;
          int maxHp;
          gdga::Armature armature; // TO SET!

        public:
          Creature();
          Creature(const Creature&);
          Creature& operator=(const Creature&);

          int getHp() const;
          int getMaxHp() const;
          const gdga::Armature& getArmature() const;

          virtual void update(float);
        };
      }
    }
  }
}

#endif
