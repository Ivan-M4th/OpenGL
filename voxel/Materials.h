#ifndef GD_VOXEL_MATERIALS_H
#define GD_VOXEL_MATERIALS_H

#include "Material.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      extern const unsigned int AIR;
      extern const unsigned int GRASS;
      extern const unsigned int DIRT;
      extern const unsigned int STONE;
      extern const unsigned int WOOD_PLANKS;
      extern const unsigned int STONE_BRICKS;
      extern const unsigned int RED_BRICKS;
      extern const unsigned int CONCRETE;

      //roches sedimentaires

      extern const unsigned int CLAY;
      extern const unsigned int ANTHRACITE;
      extern const unsigned int BITUMINOUS_COAL;
      extern const unsigned int LIGNITE;
      extern const unsigned int PEAT;
      extern const unsigned int ANHYDRITE;
      extern const unsigned int GYPSUM;
      extern const unsigned int HALITE;
      extern const unsigned int POTASH;
      extern const unsigned int LIMESTONE;
      extern const unsigned int CHALK;
      extern const unsigned int DOLOMITE;
      extern const unsigned int MARL;
      extern const unsigned int TUFA;
      extern const unsigned int PHOSPHORITE;
      extern const unsigned int DIATOMITE;
      extern const unsigned int SANDSTONE;
      extern const unsigned int RADIOLARITE;
      extern const unsigned int FLINT;
      extern const unsigned int SPICULITE;

      Material* getMaterial(unsigned int);
      unsigned int getMaterialsAmount();

      class Materials
      {
      private:
        unsigned int amount;
        Material* data;

        void deleteData();
        void setMaterial(unsigned int, const Material&);
      public:
        Materials();
        Materials(const Materials&);
        Materials& operator=(const Materials&);
        ~Materials();

        Material* getMaterial(unsigned int) const;
        unsigned int getAmount() const;
      };
    }
  }
}

#endif
