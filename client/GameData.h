#ifndef GD_CLIENT_GAMEDATA_H
#define GD_CLIENT_GAMEDATA_H

#include "../gddef.h"

#include "ObjectData.h"

#include "../utils/MemoryArray.h"

#include "objects/Tree.h"
#include "objects/Boar.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      struct GameData
      {
        //structures
        gdu::MemoryArray<ObjectData> treeDatas;
        gdu::MemoryArray<gdco::Tree> trees;

        //creatures
        gdu::MemoryArray<ObjectData> boarDatas;
        gdu::MemoryArray<gdco::Boar> boars;
      };
    }
  }
}

#endif
