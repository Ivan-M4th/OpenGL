#include "Character.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        Character::Character() : Animal()
        {
          this->name = name;
        }

        Character::Character(const Character& character) : Animal(character)
        {
          name = character.name;
        }

        Character& Character::operator=(const Character& character)
        {
          Animal::operator=(character);
          name = character.name;
          return *this;
        }

        void Character::update(float timePassed)
        {
          Animal::update(timePassed);
        }
      }
    }
  }
}
