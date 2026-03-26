#ifndef GD_CLIENT_OBJECTDATASMANAGER_H
#define GD_CLIENT_OBJECTDATASMANAGER_H

#include "../gddef.h"

#include "ObjectData.h"

#include "../utils/MemoryArray.h"

#include "../physics/SimulationDataManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      template<typename Type> class ObjectDatasManager
      {
        friend class GameDataManager;

      private:
        gdp::SimulationDataManager* simulationDataManager;
        gdu::MemoryArray<Type>* objects;
        gdu::MemoryArray<ObjectData>* objectDatas;

        void createSimulationData(ObjectData* objectData, Type* object)
        {
          assert(objectData->simulationId == -1);
          objectData->simulationId = simulationDataManager->createSimulationData(object);
        }

        void deleteSimulationData(ObjectData* objectData)
        {
          assert(objectData->simulationId != -1);
          simulationDataManager->deleteSimulationData(objectData->simulationId);
          objectData->simulationId = -1;
        }

      public:
        ObjectDatasManager()
        {
          simulationDataManager = NULL;
          objects = NULL;
          objectDatas = NULL;
        }

        ObjectDatasManager(const ObjectDatasManager& manager)
        {
          simulationDataManager = manager.simulationDataManager;
          objects = manager.objects;
          objectDatas = manager.objectDatas;
        }

        ObjectDatasManager& operator=(const ObjectDatasManager& manager)
        {
          simulationDataManager = manager.simulationDataManager;
          objects = manager.objects;
          objectDatas = manager.objectDatas;
          return *this;
        }

        bool isUsed(int objectId) const
        {
          assert(objectDatas != NULL);
          return objectDatas->isUsed(objectId);
        }

        Type* createData(int objectId)
        {
          assert(objects != NULL);
          assert(!isUsed(objectId));
          objectDatas->use(objectId);
          ObjectData* objectData = &(*objectDatas)[objectId];

          int dataId = objects->genSlot();
          Type* object = &(*objects)[dataId];

          objectData->dataId = dataId;

          createSimulationData(objectData, object);
          return object;
        }

        void deleteData(int objectId)
        {
          assert(objects != NULL);
          assert(isUsed(objectId));

          ObjectData* objectData = &(*objectDatas)[objectId];

          deleteSimulationData(objectData);

          int dataId = objectData->dataId;

          objects->free(dataId);
          objectDatas->free(objectId);

          objectData->dataId = -1;
        }

        Type* get(int objectId)
        {
          assert(objects != NULL);
          assert(isUsed(objectId));
          ObjectData* objectData = &(*objectDatas)[objectId];
          int dataId = objectData->dataId;
          return &(*objects)[dataId];
        }

        int getSimulationId(int objectId) const
        {
          assert(isUsed(objectId));
          ObjectData* objectData = &(*objectDatas)[objectId];
          return objectData->simulationId;
        }

        void setChunkPosition(int objectId, int cx, int cy, int cz)
        {
          assert(isUsed(objectId));
          ObjectData* objectData = &(*objectDatas)[objectId];
          objectData->chunkPosition.x = cx;
          objectData->chunkPosition.y = cy;
          objectData->chunkPosition.z = cz;
        }

        void setChunkPosition(int objectId, const gdm::Vector3i& chunkPosition)
        {
          assert(isUsed(objectId));
          ObjectData* objectData = &(*objectDatas)[objectId];
          objectData->chunkPosition = chunkPosition;
        }

        const gdm::Vector3i* getChunkPosition(int objectId) const
        {
          assert(isUsed(objectId));
          ObjectData* objectData = &(*objectDatas)[objectId];
          return &objectData->chunkPosition;
        }
      };
    }
  }
}

#endif
