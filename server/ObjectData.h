#ifndef GD_SERVER_OBJECTDATA_H
#define GD_SERVER_OBJECTDATA_H

#include "../gddef.h"

#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
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
