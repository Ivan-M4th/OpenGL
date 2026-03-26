#ifndef GD_SERVER_PACKETS_PLAYERUPDATEPACKET_H
#define GD_SERVER_PACKETS_PLAYERUPDATEPACKET_H

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
        class PlayerUpdatePacket : public gdn::Packet
        {
        private:
          unsigned int clientId;
          const gdso::Player* player;

        public:
          PlayerUpdatePacket(unsigned int, const gdso::Player*);
          PlayerUpdatePacket(const PlayerUpdatePacket&);
          PlayerUpdatePacket& operator=(const PlayerUpdatePacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
