#ifndef GD_PHYSICS_STUCTURE_H
#define GD_PHYSICS_STUCTURE_H

#include "../gddef.h"

#include "Object.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class Structure : public Object
      {
      public:
        Structure();
        Structure(const gdm::Vector3&);
        Structure(const Structure&);
        Structure& operator=(const Structure&);
        virtual ~Structure() override;
      };
    }
  }
}

#endif
