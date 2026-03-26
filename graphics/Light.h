#ifndef GD_GRAPHICS_LIGHT_H
#define GD_GRAPHICS_LIGHT_H

#include "../gddef.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Light
      {
      private:

        gdm::Vector3 position;
        gdm::Vector3 color;
      public:
        Light(const gdm::Vector3&, const gdm::Vector3&);
        Light(const Light&);
        Light& operator=(const Light&);

        gdm::Vector3& getPosition();
        gdm::Vector3& getColor();
      };
    }
  }
}

#endif
