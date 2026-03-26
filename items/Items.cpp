#include "Items.h"

#include <cassert>

#include "ItemTypes.h"

#include "../voxel/Materials.h"

#include "../utils/Pointer.h"

#include "../graphics/Mesh.h"
#include "../graphics/GeometryLoader.h"

#include "../items/ItemIds.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      //ItemTypes

      ItemTypes* itemTypes = NULL;
      const int ITEMS_AMOUNT = 3000;

      void createItemTypes()
      {
        itemTypes = new ItemTypes(ITEMS_AMOUNT);

        itemTypes->setItemType(0, Pointer<ItemType>(new ItemType(), false));
        itemTypes->setBlockItemType(gdv::GRASS, gdv::GRASS, 30, "Grass");
        itemTypes->setBlockItemType(gdv::DIRT, gdv::DIRT, 30, "Dirt");
        itemTypes->setBlockItemType(gdv::STONE, gdv::STONE, 30, "Stone");
        itemTypes->setBlockItemType(gdv::WOOD_PLANKS, gdv::WOOD_PLANKS, 30, "Wood Planks");
        itemTypes->setBlockItemType(gdv::STONE_BRICKS, gdv::STONE_BRICKS, 30, "Stone Bricks");
        itemTypes->setBlockItemType(gdv::RED_BRICKS, gdv::RED_BRICKS, 30, "Bricks");
        itemTypes->setBlockItemType(gdv::CONCRETE, gdv::CONCRETE, 30, "Concrete");

        //roches sedimentaires
        itemTypes->setBlockItemType(gdv::CLAY, gdv::CLAY, 30, "Clay");
        itemTypes->setBlockItemType(gdv::ANTHRACITE, gdv::ANTHRACITE, 30, "Anthracite");
        itemTypes->setBlockItemType(gdv::BITUMINOUS_COAL, gdv::BITUMINOUS_COAL, 30, "Bituminous coal");
        itemTypes->setBlockItemType(gdv::LIGNITE, gdv::LIGNITE, 30, "Lignite");
        itemTypes->setBlockItemType(gdv::PEAT, gdv::PEAT, 30, "Peat");
        itemTypes->setBlockItemType(gdv::ANHYDRITE, gdv::ANHYDRITE, 30, "Anhydrite");
        itemTypes->setBlockItemType(gdv::GYPSUM, gdv::GYPSUM, 30, "Gypsum");
        itemTypes->setBlockItemType(gdv::HALITE, gdv::HALITE, 30, "Halite");
        itemTypes->setBlockItemType(gdv::POTASH, gdv::POTASH, 30, "Potash");
        itemTypes->setBlockItemType(gdv::LIMESTONE, gdv::LIMESTONE, 30, "Limestone");
        itemTypes->setBlockItemType(gdv::CHALK, gdv::CHALK, 30, "Chalk");
        itemTypes->setBlockItemType(gdv::DOLOMITE, gdv::DOLOMITE, 30, "Dolomite");
        itemTypes->setBlockItemType(gdv::MARL, gdv::MARL, 30, "Marl");
        itemTypes->setBlockItemType(gdv::TUFA, gdv::TUFA, 30, "Tufa");
        itemTypes->setBlockItemType(gdv::PHOSPHORITE, gdv::PHOSPHORITE, 30, "Phosphorite");
        itemTypes->setBlockItemType(gdv::DIATOMITE, gdv::DIATOMITE, 30, "Diatomite");
        itemTypes->setBlockItemType(gdv::SANDSTONE, gdv::SANDSTONE, 30, "Sandstone");
        itemTypes->setBlockItemType(gdv::RADIOLARITE, gdv::RADIOLARITE, 30, "Radiolarite");
        itemTypes->setBlockItemType(gdv::FLINT, gdv::FLINT, 30, "Flint");
        itemTypes->setBlockItemType(gdv::SPICULITE, gdv::SPICULITE, 30, "Spiculite");

        itemTypes->setItemType(gdi::STONE_PICKAXE, Pointer<ItemType>(new ItemType(1, 3, "Pickaxe"), false));
      }

      void deleteItemTypes()
      {
        delete itemTypes;
        itemTypes = NULL;
      }

      ItemType* getItemType(unsigned int id)
      {
        assert(itemTypes != NULL);
        return itemTypes->getItemType(id);
      }
    }
  }
}
