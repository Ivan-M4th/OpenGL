#include "ItemAssets.h"

#include "Assets.h"

#include "../voxel/Materials.h"

#include "../items/ItemIds.h"

namespace gt
{
  namespace doubovik
  {
    namespace data
    {
      ItemAsset* ITEMASSETS = NULL;
      const int ITEMASSETS_AMOUNT = 3000;

      void createItemAsset(int meshId, int textureId, int iconMeshId, int iconTexture, ItemAsset* itemAsset)
      {
        itemAsset->meshId = meshId;
        itemAsset->textureId = textureId;

        itemAsset->iconMeshId = iconMeshId;
        itemAsset->iconTexture = iconTexture;
      }

      void createItemAsset(int meshId, int textureId, int iconMeshId, int iconTexture, int assetId)
      {
        createItemAsset(meshId, textureId, iconMeshId, iconTexture, ITEMASSETS + assetId);
      }

      void createBlockAssets()
      {
        for(int i=0;i<gdv::getMaterialsAmount();i++)
        {
          createItemAsset(i, TERRAIN_ATLAS_TEXTURE, i, TERRAIN_ATLAS_TEXTURE, i);
        }
      }

      void createItemAssets()
      {
        ITEMASSETS = new ItemAsset[ITEMASSETS_AMOUNT];

        createBlockAssets();

        createItemAsset(STONE_PICKAXE_MESH, STONE_PICKAXE_TEXTURE, 1, TERRAIN_ATLAS_TEXTURE, gdi::STONE_PICKAXE);
      }

      void deleteItemAssets()
      {
        delete [] ITEMASSETS;
        ITEMASSETS = NULL;
      }

      ItemAsset* getItemAsset(int id)
      {
        assert(ITEMASSETS != NULL);
        return ITEMASSETS + id;
      }
    }
  }
}
