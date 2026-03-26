#ifndef GD_PHYSICS_SIMULATIONDATA_H
#define GD_PHYSICS_SIMULATIONDATA_H

#include "../gddef.h"

#include "Simulation.h"

#include "../math/geometry/AABB.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      struct SimulationData
      {
        Simulation* simulation = NULL;
        gdu::MemoryArray<ObjectSimulationData>* objects = NULL;
        gdu::MemoryArray<gdmg::AABB>* aabbs = NULL;
      };
    }
  }
}

#endif
