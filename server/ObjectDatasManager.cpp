#include "ObjectDatasManager.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      ObjectDatasManager::ObjectDatasManager()
      {
        objectDatas = NULL;
      }

      ObjectDatasManager::ObjectDatasManager(const ObjectDatasManager& manager)
      {
        objectDatas = manager.objectDatas;
      }

      ObjectDatasManager& ObjectDatasManager::operator=(const ObjectDatasManager& manager)
      {
        objectDatas = manager.objectDatas;
        return *this;
      }

      bool ObjectDatasManager::isUsed(int objectId) const
      {
        assert(objectDatas != NULL);
        return objectDatas->isUsed(objectId);
      }

      void ObjectDatasManager::createSimulationData(gdp::SimulationDataManager* simulationDataManager, gdp::Object* object, int objectId)
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        assert(objectData->simulationId == -1);
        objectData->simulationId = simulationDataManager->createSimulationData(object);
      }

      void ObjectDatasManager::deleteSimulationData(gdp::SimulationDataManager* simulationDataManager, int objectId)
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        assert(objectData->simulationId != -1);
        simulationDataManager->deleteSimulationData(objectData->simulationId);
        objectData->simulationId = -1;
      }

      int ObjectDatasManager::getSimulationId(int objectId) const
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        return objectData->simulationId;
      }

      void ObjectDatasManager::setChunkPosition(int objectId, int cx, int cy, int cz)
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        objectData->chunkPosition.x = cx;
        objectData->chunkPosition.y = cy;
        objectData->chunkPosition.z = cz;
      }

      void ObjectDatasManager::setChunkPosition(int objectId, const gdm::Vector3i& chunkPosition)
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        objectData->chunkPosition = chunkPosition;
      }

      const gdm::Vector3i* ObjectDatasManager::getChunkPosition(int objectId) const
      {
        assert(isUsed(objectId));
        ObjectData* objectData = &(*objectDatas)[objectId];
        return &objectData->chunkPosition;
      }
    }
  }
}
