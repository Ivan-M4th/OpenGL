#include "Character.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        Character::Character() : Animal()
        {
          
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
      }
    }
  }
}
