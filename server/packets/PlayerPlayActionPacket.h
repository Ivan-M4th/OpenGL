#ifndef GD_SERVER_PACKETS_PLAYERPLAYACTIONPACKET_H
#define GD_SERVER_PACKETS_PLAYERPLAYACTIONPACKET_H

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
        class PlayerPlayActionPacket : public gdn::Packet
        {
        private:
          unsigned int clientId;
          unsigned int actionId;

        public:
          PlayerPlayActionPacket(unsigned int, unsigned int);
          PlayerPlayActionPacket(const PlayerPlayActionPacket&);
          PlayerPlayActionPacket& operator=(const PlayerPlayActionPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
