#ifndef GD_SERVER_OBJECTSTOUPDATE_H
#define GD_SERVER_OBJECTSTOUPDATE_H

#include "../gddef.h"

#include "../utils/ArrayList.h"
#include "../utils/LinkedHashList.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      struct ObjectsToUpdate
      {
        gdu::LinkedHashList<int> simulationIds;

        ArrayList<int> boars;
      };
    }
  }
}

#endif
