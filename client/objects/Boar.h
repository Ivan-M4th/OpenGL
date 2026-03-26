#ifndef GD_CLIENT_OBJECTS_BOAR_H
#define GD_CLIENT_OBJECTS_BOAR_H

#include "Animal.h"

#include "../../graphics/animation/ArmatureAnimator.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class Boar : public Animal
        {
        private:
          gdga::ArmatureAnimator animator;

        public:
          Boar();
          Boar(const Boar&);
          Boar& operator=(const Boar&);

          virtual void update(float) override;
        };
      }
    }
  }
}

#endif
