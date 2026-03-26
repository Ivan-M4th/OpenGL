#include "Animal.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        Animal::Animal() : Creature()
        {

        }

        Animal::Animal(const Animal& animal) : Creature(animal), inventory(animal.inventory)
        {

        }

        Animal& Animal::operator=(const Animal& animal)
        {
          Creature::operator=(animal);
          inventory = animal.inventory;
          return *this;
        }

        gdi::Inventory* Animal::getInventory()
        {
          return &inventory;
        }
      }
    }
  }
}
