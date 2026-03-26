#ifndef GD_CLIENT_GAMEDATAMANAGER_H
#define GD_CLIENT_GAMEDATAMANAGER_H

#include "../gddef.h"

#include "GameData.h"
#include "ObjectDatasManager.h"

#include "../physics/Object.h"
#include "../physics/SimulationDataManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      class GameDataManager
      {
      private:
        GameData* gameData;
        gdp::SimulationDataManager* simulationDataManager;

        mutable ObjectDatasManager<gdco::Tree> treeDatasManager;
        mutable ObjectDatasManager<gdco::Boar> boarDatasManager;

      public:
        GameDataManager(GameData*, gdp::SimulationDataManager*);
        GameDataManager(const GameDataManager&);
        GameDataManager& operator=(const GameDataManager&);

        ObjectDatasManager<gdco::Tree>* getTreesManager() const;
        ObjectDatasManager<gdco::Boar>* getBoarsManager() const;
        gdp::Simulation* getSimulation() const;
      };
    }
  }
}

#endif
