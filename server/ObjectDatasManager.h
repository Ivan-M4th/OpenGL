#ifndef GD_SERVER_OBJECTDATASMANAGER_H
#define GD_SERVER_OBJECTDATASMANAGER_H

#include "../gddef.h"

#include "ObjectData.h"

#include "../utils/MemoryArray.h"

#include "../physics/Object.h"
#include "../physics/SimulationDataManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      class ObjectDatasManager
      {
        friend class GameDataManager;

      private:
        gdu::MemoryArray<ObjectData>* objectDatas;

      public:
        ObjectDatasManager();
        ObjectDatasManager(const ObjectDatasManager&);
        ObjectDatasManager& operator=(const ObjectDatasManager&);

        bool isUsed(int) const;

        void createSimulationData(gdp::SimulationDataManager*, gdp::Object*, int);
        void deleteSimulationData(gdp::SimulationDataManager*, int);
        int getSimulationId(int) const;

        void setChunkPosition(int, int, int, int); //id, position
        void setChunkPosition(int, const gdm::Vector3i&);
        const gdm::Vector3i* getChunkPosition(int) const;
      };
    }
  }
}

#endif
