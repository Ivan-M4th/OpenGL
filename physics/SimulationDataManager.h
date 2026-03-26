#ifndef GD_PHYSICS_SIMULATIONDATAMANAGER_H
#define GD_PHYSICS_SIMULATIONDATAMANAGER_H

#include "SimulationData.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class SimulationDataManager
      {
      private:
        SimulationData* simulationData;

      public:
        SimulationDataManager(SimulationData*);
        SimulationDataManager(const SimulationDataManager&);
        SimulationDataManager& operator=(const SimulationDataManager&);

        int createSimulationData(Object*);
        void deleteSimulationData(int);

        Simulation* getSimulation() const;
      };
    }
  }
}

#endif
