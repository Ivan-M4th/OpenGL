#include "Materials.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {

      const unsigned int MATERIALS_AMOUNT = 28;

      const unsigned int AIR = 0;
      const unsigned int GRASS = 1;
      const unsigned int DIRT = 2;
      const unsigned int STONE = 3;
      const unsigned int WOOD_PLANKS = 4;
      const unsigned int STONE_BRICKS = 5;
      const unsigned int RED_BRICKS = 6;
      const unsigned int CONCRETE = 7;
      const unsigned int CLAY = 8;
      const unsigned int ANTHRACITE = 9;
      const unsigned int BITUMINOUS_COAL = 10;
      const unsigned int LIGNITE = 11;
      const unsigned int PEAT = 12;
      const unsigned int ANHYDRITE = 13;
      const unsigned int GYPSUM = 14;
      const unsigned int HALITE = 15;
      const unsigned int POTASH = 16;
      const unsigned int LIMESTONE = 17;
      const unsigned int CHALK = 18;
      const unsigned int DOLOMITE = 19;
      const unsigned int MARL = 20;
      const unsigned int TUFA = 21;
      const unsigned int PHOSPHORITE = 22;
      const unsigned int DIATOMITE = 23;
      const unsigned int SANDSTONE = 24;
      const unsigned int RADIOLARITE = 25;
      const unsigned int FLINT = 26;
      const unsigned int SPICULITE = 27;

      const Materials MATERIALS;

      Material* getMaterial(unsigned int id)
      {
        return MATERIALS.getMaterial(id);
      }

      unsigned int getMaterialsAmount()
      {
        return MATERIALS.getAmount();
      }

      Materials::Materials()
      {
        amount = MATERIALS_AMOUNT;
        data = new Material[amount];

        setMaterial(AIR, Material(0,0,0, false, false));
        setMaterial(GRASS, Material(0,1,2));
        setMaterial(DIRT, Material(2,2,2));
        setMaterial(STONE, Material(3, 3, 3));
        setMaterial(WOOD_PLANKS, Material(4, 4, 4));
        setMaterial(STONE_BRICKS, Material(5, 5, 5));
        setMaterial(RED_BRICKS, Material(6, 6, 6));
        setMaterial(CONCRETE, Material(7, 7, 7));
        //roches sedimentaires
        setMaterial(CLAY, Material(8, 8, 8));
        setMaterial(ANTHRACITE, Material(9, 9, 9));
        setMaterial(BITUMINOUS_COAL, Material(10, 10, 10));
        setMaterial(LIGNITE, Material(11, 11, 11));
        setMaterial(PEAT, Material(12, 12, 12));
        setMaterial(ANHYDRITE, Material(13, 13, 13));
        setMaterial(GYPSUM, Material(14, 14, 14));
        setMaterial(HALITE, Material(15, 15, 15));
        setMaterial(POTASH, Material(16, 16, 16));
        setMaterial(LIMESTONE, Material(17, 17, 17));
        setMaterial(CHALK, Material(18, 18, 18));
        setMaterial(DOLOMITE, Material(19, 19, 19));
        setMaterial(MARL, Material(20, 20, 20));
        setMaterial(TUFA, Material(21, 21, 21));
        setMaterial(PHOSPHORITE, Material(22, 22, 22));
        setMaterial(DIATOMITE, Material(23, 23, 23));
        setMaterial(SANDSTONE, Material(24, 24, 24));
        setMaterial(RADIOLARITE, Material(25, 25, 25));
        setMaterial(FLINT, Material(26, 26, 26));
        setMaterial(SPICULITE, Material(27, 27, 27));
      }

      Materials::Materials(const Materials& materials)
      {
        amount = materials.amount;
        data = new Material[amount];
        for(unsigned int i=0;i<amount;i++)
        {
          *(data + i) = *(materials.data + i);
        }
      }

      Materials& Materials::operator=(const Materials& materials)
      {
        deleteData();
        amount = materials.amount;
        data = new Material[amount];
        for(unsigned int i=0;i<amount;i++)
        {
          *(data + i) = *(materials.data + i);
        }
        return *this;
      }

      Materials::~Materials()
      {
        deleteData();
      }

      void Materials::deleteData()
      {
        delete[] data;
      }

      void Materials::setMaterial(unsigned int id, const Material& material)
      {
        assert(id < amount);
        *(data + id) = material;
      }

      Material* Materials::getMaterial(unsigned int id) const
      {
        assert(id < amount);
        return data + id;
      }

      unsigned int Materials::getAmount() const
      {
        return amount;
      }
    }
  }
}
