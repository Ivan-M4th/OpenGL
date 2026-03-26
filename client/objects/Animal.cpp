#include "Animal.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        Animal::Animal() : Creature()
        {

        }

        Animal::Animal(const Animal& animal) : Creature(animal)
        {

        }

        Animal& Animal::operator=(const Animal& animal)
        {
          Creature::operator=(animal);
          return *this;
        }

        void Animal::update(float timePassed)
        {
          Creature::update(timePassed);
        }
      }
    }
  }
}
