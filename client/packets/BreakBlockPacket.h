#ifndef GD_CLIENT_PACKETS_BREAKBLOCKPACKET_H
#define GD_CLIENT_PACKETS_BREAKBLOCKPACKET_H

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
        class BreakBlockPacket : public gdn::Packet
        {
        private:
          int bx;
          int by;
          int bz;

        public:
          BreakBlockPacket(int, int, int);
          BreakBlockPacket(const BreakBlockPacket&);
          BreakBlockPacket& operator=(const BreakBlockPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
