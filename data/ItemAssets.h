#ifndef GD_DATA_ITEMASSETS_H
#define GD_DATA_ITEMASSETS_H

#include "../gddef.h"

namespace gt
{
  namespace doubovik
  {
    namespace data
    {

      struct ItemAsset
      {
        int meshId = -1;
        int textureId = -1;

        int iconMeshId = -1;
        int iconTexture = -1;
      };

      void createItemAssets();
      void deleteItemAssets();

      ItemAsset* getItemAsset(int);
    }
  }
}

#endif
