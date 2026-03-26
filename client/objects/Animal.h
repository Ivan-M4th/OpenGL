#ifndef GD_CLIENT_OBJECTS_ANIMAL_H
#define GD_CLIENT_OBJECTS_ANIMAL_H

#include "../../gddef.h"

#include "Creature.h"

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
        class Animal : public Creature
        {
        public:
          Animal();
          Animal(const Animal&);
          Animal& operator=(const Animal&);

          virtual void update(float);
        };
      }
    }
  }
}

#endif
