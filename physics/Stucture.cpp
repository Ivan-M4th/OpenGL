#include "Structure.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      Structure::Structure() : Object()
      {
        physicalInformation.moveable = false;
        physicalInformation.mass = 100000;
      }

      Structure::Structure(const gdm::Vector3& position) : Object(position)
      {
        physicalInformation.moveable = false;
        physicalInformation.mass = 100000;
      }

      Structure::Structure(const Structure& structure) : Object(structure)
      {

      }

      Structure& Structure::operator=(const Structure& structure)
      {
        Object::operator=(structure);
        return *this;
      }

      Structure::~Structure()
      {

      }
    }
  }
}
