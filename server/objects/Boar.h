#ifndef GD_SERVER_OBJECTS_BOAR_H
#define GD_SERVER_OBJECTS_BOAR_H

#include "Animal.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        class Boar : public Animal
        {
        public:
          Boar();
          Boar(const Boar&);
          Boar& operator=(const Boar&);
        };
      }
    }
  }
}

#endif
