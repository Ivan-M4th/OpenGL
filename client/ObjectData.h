#ifndef GD_CLIENT_OBJECTDATA_H
#define GD_CLIENT_OBJECTDATA_H

#include "../gddef.h"

#include "../physics/Object.h"

#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      struct ObjectData
      {
        int dataId = -1;
        int simulationId = -1;

        gdm::Vector3i chunkPosition;
      };
    }
  }
}

#endif
