#include "Creature.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        Creature::Creature() : gdp::Object()
        {
          hp = 1000;
          maxHp = 1000;
          physicalInformation.objectType = gdp::CONTROLED_OBJECT;
          physicalInformation.useGravity = true;
        }

        Creature::Creature(const Creature& creature) : gdp::Object(creature)
        {
          hp = creature.hp;
          maxHp = creature.maxHp;
        }

        Creature& Creature::operator=(const Creature& creature)
        {
          gdp::Object::operator=(creature);
          hp = creature.hp;
          maxHp = creature.maxHp;
          return *this;
        }

        int Creature::getHp() const
        {
          return hp;
        }

        int Creature::getMaxHp() const
        {
          return maxHp;
        }
      }
    }
  }
}
