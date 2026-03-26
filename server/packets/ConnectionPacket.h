#ifndef GD_SERVER_PACKETS_CONNECTIONPACKET_H
#define GD_SERVER_PACKETS_CONNECTIONPACKET_H

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
        class ConnectionPacket : public gdn::Packet
        {
        private:
          unsigned int maxPlayers;

        public:
          ConnectionPacket(unsigned int);
          ConnectionPacket(const ConnectionPacket&);
          ConnectionPacket& operator=(const ConnectionPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
