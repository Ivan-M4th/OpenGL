#ifndef GD_SERVER_LISTENERS_PACKETLISTENER_H
#define GD_SERVER_LISTENERS_PACKETLISTENER_H

#include "../../gddef.h"

#include "../../utils/BufferReader.h"

#include "../../events/Listener.h"

#include "../events/PacketReceiveEvent.h"

#include "../ServerManager.h"
#include "../Players.h"

#include "../../networking/Server.h"

#include "../../voxel/Terrain.h"

#include "../voxel/TerrainSender.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        class PacketListener : public gde::Listener<gdse::PacketReceiveEvent>
        {
        private:
          ServerManager* serverManager;
          Players* players;
          gdv::Terrain* terrain;
          gdsv::TerrainSender* terrainSender;

          void handleConnection(int, gdu::BufferReader*);
          void handleClientInfo(int, gdu::BufferReader*);

          void handleGameData(int, gdu::BufferReader*);
          void handleSpawnRequest(int, gdu::BufferReader*);
          void handleClientUpdate(unsigned int, gdu::BufferReader*) const;

          void handleTerrainInfo(int, gdu::BufferReader*);
          void handleChunkRequest(int, gdu::BufferReader*) const;
          void handlePlaceBlock(unsigned int, gdu::BufferReader*) const;
          void handleBreakBlock(unsigned int, gdu::BufferReader*) const;
          void handleUpdateGridPosition(int, gdu::BufferReader*) const;

          void handleInventoryInfo(unsigned int, gdu::BufferReader*) const;
          void handleSwapItems(unsigned int, gdu::BufferReader*) const;
          void handleSelectedInventorySlot(unsigned int, gdu::BufferReader*) const;
        public:
          PacketListener(ServerManager*, Players*, gdv::Terrain*, gdsv::TerrainSender*);
          PacketListener(const PacketListener&);
          PacketListener& operator=(const PacketListener&);

          void onEvent(gdse::PacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
