#include "Creature.h"

#include "../../physics/PhysicalInformation.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
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

        Creature::Creature(const Creature& creature) : gdp::Object(creature), armature(creature.armature)
        {
          hp = creature.hp;
          maxHp = creature.maxHp;
        }

        Creature& Creature::operator=(const Creature& creature)
        {
          gdp::Object::operator=(creature);
          hp = creature.hp;
          maxHp = creature.maxHp;
          armature = creature.armature;
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

        const gdga::Armature& Creature::getArmature() const
        {
          return armature;
        }

        void Creature::update(float timePassed)
        {
          gdp::Object::update(timePassed);
        }
      }
    }
  }
}
