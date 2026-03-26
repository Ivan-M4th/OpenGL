#ifndef GD_SERVER_GAMEDATA_H
#define GD_SERVER_GAMEDATA_H

#include "../gddef.h"

#include "ObjectData.h"

#include "objects/Tree.h"
#include "objects/Boar.h"

#include "../utils/MemoryArray.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {

      struct GameData
      {
        //structures
        gdu::MemoryArray<ObjectData> treeDatas;
        gdu::MemoryArray<gdso::Tree> trees;

        //creatures
        gdu::MemoryArray<ObjectData> boarDatas;
        gdu::MemoryArray<gdso::Boar> boars;
      };

    }
  }
}

#endif
