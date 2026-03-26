#include "Boar.h"

#include "../../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        Boar::Boar() : Animal()
        {
          collider = gdd::getConvexShape(gdd::BOAR_HITBOX_SHAPE);
          transformation.scale = gdm::Vector3(0.3, 0.3, 0.3);
        }

        Boar::Boar(const Boar& boar) : Animal(boar)
        {

        }

        Boar& Boar::operator=(const Boar& boar)
        {
          Animal::operator=(boar);
          return *this;
        }
      }
    }
  }
}
