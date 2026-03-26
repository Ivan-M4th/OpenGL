#ifndef GD_UTILS_UTILITIES_H
#define GD_UTILS_UTILITIES_H

#include "../gddef.h"

#include "String.h"
#include "ArrayList.h"

#include "../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      gdm::Matrix4x4 toMatrix4x4(const String&);
      ArrayList<gdm::Matrix4x4> toMatrix4x4Array(const String&);
    }
  }
}

#endif
