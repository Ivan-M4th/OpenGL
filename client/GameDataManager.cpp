#include "GameDataManager.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      GameDataManager::GameDataManager(GameData* gameData, gdp::SimulationDataManager* simulationDataManager)
      {
        this->gameData = gameData;
        this->simulationDataManager = simulationDataManager;

        treeDatasManager.simulationDataManager = simulationDataManager;
        treeDatasManager.objects = &gameData->trees;
        treeDatasManager.objectDatas = &gameData->treeDatas;

        boarDatasManager.simulationDataManager = simulationDataManager;
        boarDatasManager.objects = &gameData->boars;
        boarDatasManager.objectDatas = &gameData->boarDatas;
      }

      GameDataManager::GameDataManager(const GameDataManager& manager)
      {
        gameData = manager.gameData;
        simulationDataManager = manager.simulationDataManager;
        treeDatasManager = manager.treeDatasManager;
        boarDatasManager = manager.boarDatasManager;
      }

      GameDataManager& GameDataManager::operator=(const GameDataManager& manager)
      {
        gameData = manager.gameData;
        simulationDataManager = manager.simulationDataManager;
        treeDatasManager = manager.treeDatasManager;
        boarDatasManager = manager.boarDatasManager;
        return *this;
      }

      ObjectDatasManager<gdco::Tree>* GameDataManager::getTreesManager() const
      {
        return &treeDatasManager;
      }

      ObjectDatasManager<gdco::Boar>* GameDataManager::getBoarsManager() const
      {
        return &boarDatasManager;
      }

      gdp::Simulation* GameDataManager::getSimulation() const
      {
        return simulationDataManager->getSimulation();
      }
    }
  }
}
