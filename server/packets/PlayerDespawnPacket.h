#ifndef GD_SERVER_PACKETS_PLAYERDESPAWNPACKET_H
#define GD_SERVER_PACKETS_PLAYERDESPAWNPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        class PlayerDespawnPacket : public gdn::Packet
        {
        private:
          unsigned int clientId;

        public:
          PlayerDespawnPacket(unsigned int);
          PlayerDespawnPacket(PlayerDespawnPacket&);
          PlayerDespawnPacket& operator=(const PlayerDespawnPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
