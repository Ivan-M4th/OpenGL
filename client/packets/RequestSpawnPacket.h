#ifndef GD_CLIENT_PACKETS_REQUESTSPAWNPACKET_H
#define GD_CLIENT_PACKETS_REQUESTSPAWNPACKET_H

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
        class RequestSpawnPacket : public gdn::Packet
        {
          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
