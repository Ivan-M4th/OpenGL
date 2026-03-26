#ifndef GD_CLIENT_LISTENERS_PACKETLISTENER_H
#define GD_CLIENT_LISTENERS_PACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/PacketReceiveEvent.h"

#include "../../utils/BufferReader.h"

#include "../../networking/Client.h"

#include "../Players.h"
#include "../GameDataManager.h"

#include "../../voxel/ChunkGrid.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class PacketListener : public gde::Listener<gdce::PacketReceiveEvent>
        {
        private:
          gdn::Client* client;
          Players* players;
          gdv::ChunkGrid* chunkGrid;
          GameDataManager* gameDataManager;

          void handleConnection(gdu::BufferReader*) const;
          void handleServerInfo(gdu::BufferReader*) const;

          void handleGameInfo(gdu::BufferReader*) const;
          void handleMainPlayerSpawn(gdu::BufferReader*) const;
          void handlePlayerSpawn(gdu::BufferReader*) const;
          void handlePlayerUpdate(gdu::BufferReader*) const;
          void handlePlayerDespawn(gdu::BufferReader*) const;
          void handlePlayerPlayAction(gdu::BufferReader*) const;
          void handleBoarUpdate(gdu::BufferReader*) const;

          void handleTerrainInfo(gdu::BufferReader*) const;
          void handleChunkReceive(gdu::BufferReader*) const;
          void handleSetBlock(gdu::BufferReader*) const;
          void handleChunkTreesReceive(gdu::BufferReader*) const;
          void handleChunkBoarsReceive(gdu::BufferReader*) const;

          void handleInventoryInfo(gdu::BufferReader*) const;
          void handleSetItem(gdu::BufferReader*) const;
          void handlePlayerEquipedItem(gdu::BufferReader*) const;

        public:
          PacketListener(gdn::Client*, Players*, gdv::ChunkGrid*, GameDataManager*);
          PacketListener(const PacketListener&);
          PacketListener& operator=(const PacketListener&);

          void onEvent(gdce::PacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
