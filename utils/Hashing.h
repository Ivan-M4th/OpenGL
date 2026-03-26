#ifndef GD_UTILS_HASHING_H
#define GD_UTILS_HASHING_H

#include "../gddef.h"

#include "../math/Vector2i.h"
#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      unsigned int hash(unsigned int);
      unsigned int hash(int);
      unsigned int hash(unsigned int, unsigned int);
      unsigned int hash(int, int);

      unsigned int hash(const gdm::Vector2i&);
      unsigned int hash(const gdm::Vector3i&);
    }
  }
}

#endif
