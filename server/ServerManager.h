#ifndef GD_SERVER_SERVERMANAGER_H
#define GD_SERVER_SERVERMANAGER_H

#include "../gddef.h"

#include "GameDataManager.h"

#include "../networking/Server.h"

#include "../utils/Buffer.h"

#include "../items/ItemStack.h"

#include "../voxel/Chunk.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      class ServerManager
      {
      private:
        gdn::Server* server;
        gdu::Buffer* buffer;

      public:
        ServerManager(gdn::Server*, gdu::Buffer*);

        bool isOnline(int) const;

        void sendSetBlockPacket(int, int, int, int); //abs pos, material
        void sendPlayerEquipedItemPacket(int, int, const gdi::ItemStack*); //client, location, item
        void sendChunkPacket(int, int, int, int, const gdv::Chunk*); //client, abs pos, chunk
        void sendChunkTreesPacket(int, GameDataManager*, int, int, int, const ArrayList<int>*);
        void sendChunkBoarsPacket(int, GameDataManager*, int, int, int, const ArrayList<int>*);
        void sendUpdateBoarPacket(GameDataManager*, int);
      };
    }
  }
}

#endif
