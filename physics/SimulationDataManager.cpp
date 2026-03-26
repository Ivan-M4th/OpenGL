#include "SimulationDataManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      SimulationDataManager::SimulationDataManager(SimulationData* simulationData)
      {
        this->simulationData = simulationData;
      }

      SimulationDataManager::SimulationDataManager(const SimulationDataManager& manager)
      {
        simulationData = manager.simulationData;
      }

      SimulationDataManager& SimulationDataManager::operator=(const SimulationDataManager& manager)
      {
        simulationData = manager.simulationData;
        return *this;
      }

      int SimulationDataManager::createSimulationData(Object* object)
      {
        int simulationId = simulationData->objects->genSlot();
        (*simulationData->objects)[simulationId].object = object;
        (*simulationData->objects)[simulationId].aabbId = simulationData->aabbs->genSlot();

        return simulationId;
      }

      void SimulationDataManager::deleteSimulationData(int simulationId) //ok
      {
        simulationData->simulation->remove(simulationId);
        (*simulationData->objects)[simulationId].object = NULL;
        simulationData->aabbs->free((*simulationData->objects)[simulationId].aabbId);
        (*simulationData->objects)[simulationId].aabbId = -1;

        simulationData->objects->free(simulationId);
      }

      Simulation* SimulationDataManager::getSimulation() const
      {
        return simulationData->simulation;
      }
    }
  }
}
