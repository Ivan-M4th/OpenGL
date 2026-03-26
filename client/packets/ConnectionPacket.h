#ifndef GD_CLIENT_PACKETS_CONNECTIONPACKET_H
#define GD_CLIENT_PACKETS_CONNECTIONPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        class ConnectionPacket : public gdn::Packet
        {
        public:
          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
