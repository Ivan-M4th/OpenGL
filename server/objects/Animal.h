#ifndef GD_SERVER_OBJECTS_ANIMAL_H
#define GD_SERVER_OBJECTS_ANIMAL_H

#include "../../gddef.h"

#include "Creature.h"

#include "../../math/Vector3.h"

#include "../../items/Inventory.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        class Animal : public Creature
        {
        protected:
          gdi::Inventory inventory;

        public:
          Animal();
          Animal(const Animal&);
          Animal& operator=(const Animal&);

          gdi::Inventory* getInventory();
        };
      }
    }
  }
}

#endif
