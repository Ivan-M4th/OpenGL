#ifndef GD_SERVER_GAMEDATAMANAGER_H
#define GD_SERVER_GAMEDATAMANAGER_H

#include "../gddef.h"

#include "GameData.h"
#include "ObjectDatasManager.h"

#include "../physics/SimulationDataManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {

      class GameDataManager
      {
      private:
        GameData* gameData;
        gdp::SimulationDataManager* simulationDataManager;

        mutable ObjectDatasManager treeDatasManager;
        mutable ObjectDatasManager boarDatasManager;

      public:
        GameDataManager(GameData*, gdp::SimulationDataManager*);
        GameDataManager(const GameDataManager&);
        GameDataManager& operator=(const GameDataManager&);

        void createTree(int*, gdso::Tree**);
        void deleteTree(int);
        gdso::Tree* getTree(int) const;

        void createBoar(int*, gdso::Boar**);
        void deleteBoar(int);
        gdso::Boar* getBoar(int) const;

        ObjectDatasManager* getTreesManager() const;
        ObjectDatasManager* getBoarsManager() const;

        gdp::SimulationDataManager* getSimulationDataManager() const;
      };

    }
  }
}

#endif
