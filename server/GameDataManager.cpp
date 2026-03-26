#include "GameDataManager.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      GameDataManager::GameDataManager(GameData* gameData, gdp::SimulationDataManager* simulationDataManager)
      {
        this->gameData = gameData;
        this->simulationDataManager = simulationDataManager;

        treeDatasManager.objectDatas = &gameData->treeDatas;
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

      void GameDataManager::createTree(int* objectId, gdso::Tree** tree)
      {
        *objectId = gameData->treeDatas.genSlot();

        ObjectData* objectData = &gameData->treeDatas[*objectId];

        int treeId = gameData->trees.genSlot();
        *tree = &gameData->trees[treeId];

        objectData->dataId = treeId;

        treeDatasManager.createSimulationData(simulationDataManager, *tree, *objectId);
      }

      void GameDataManager::deleteTree(int objectId)
      {
        std::cout << "deleteing tree: " << objectId << std::endl;
        assert(gameData->treeDatas.isUsed(objectId));
        //todo: check if tree

        ObjectData* objectData = &gameData->treeDatas[objectId];

        treeDatasManager.deleteSimulationData(simulationDataManager, objectId);

        int treeId = objectData->dataId;

        gameData->trees.free(treeId);
        gameData->treeDatas.free(objectId);

        objectData->dataId = -1;

        std::cout << "tree deleted!" << std::endl;
      }

      gdso::Tree* GameDataManager::getTree(int objectId) const
      {
        assert(gameData->treeDatas.isUsed(objectId));
        ObjectData* objectData = &gameData->treeDatas[objectId];
        int treeId = objectData->dataId;
        return &gameData->trees[treeId];
      }

      void GameDataManager::createBoar(int* objectId, gdso::Boar** boar)
      {
        *objectId = gameData->boarDatas.genSlot();

        ObjectData* objectData = &gameData->boarDatas[*objectId];

        int boarId = gameData->boars.genSlot();
        *boar = &gameData->boars[boarId];

        objectData->dataId = boarId;

        boarDatasManager.createSimulationData(simulationDataManager, *boar, *objectId);
      }

      void GameDataManager::deleteBoar(int objectId)
      {
        std::cout << "deleteing boar: " << objectId << std::endl;
        assert(gameData->boarDatas.isUsed(objectId));
        //todo: check if tree

        ObjectData* objectData = &gameData->boarDatas[objectId];

        boarDatasManager.deleteSimulationData(simulationDataManager, objectId);

        int boarId = objectData->dataId;

        gameData->boars.free(boarId);
        gameData->boarDatas.free(objectId);

        objectData->dataId = -1;

        std::cout << "boar deleted!" << std::endl;
      }

      gdso::Boar* GameDataManager::getBoar(int objectId) const
      {
        assert(gameData->boarDatas.isUsed(objectId));
        ObjectData* objectData = &gameData->boarDatas[objectId];
        int boarId = objectData->dataId;
        return &gameData->boars[boarId];
      }

      ObjectDatasManager* GameDataManager::getTreesManager() const
      {
        return &treeDatasManager;
      }

      ObjectDatasManager* GameDataManager::getBoarsManager() const
      {
        return &boarDatasManager;
      }

      gdp::SimulationDataManager* GameDataManager::getSimulationDataManager() const
      {
        return simulationDataManager;
      }
    }
  }
}
