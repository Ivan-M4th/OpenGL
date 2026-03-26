#ifndef GD_SERVER_PACKETS_PLAYERSPAWNPACKET_H
#define GD_SERVER_PACKETS_PLAYERSPAWNPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

#include "../objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        class PlayerSpawnPacket : public gdn::Packet
        {
        private:
          unsigned int clientId;
          const gdso::Player* player;

        public:
          PlayerSpawnPacket(unsigned int, gdso::Player*);
          PlayerSpawnPacket(const PlayerSpawnPacket&);
          PlayerSpawnPacket& operator=(const PlayerSpawnPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
