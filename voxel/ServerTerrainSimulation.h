#ifndef GD_VOXEL_SERVERTERRAINSIMULATION_H
#define GD_VOXEL_SERVERTERRAINSIMULATION_H

#include "../gddef.h"

#include "Region.h"
#include "../utils/ArrayList.h"
#include "../utils/Pointer.h"
#include "../physics/Object.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ServerTerrainSimulation
      {
      private:
        Region* region;
        ArrayList<Pointer<gdp::Object>>* objects;
      public:
        ServerTerrainSimulation(Region*, ArrayList<Pointer<gdp::Object>>*);
        ServerTerrainSimulation(const ServerTerrainSimulation&);
        ServerTerrainSimulation& operator=(const ServerTerrainSimulation&);

        void updateCollisions(gdp::Object*) const;
        void update(float);
      };
    }
  }
}

#endif
