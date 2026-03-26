#ifndef GD_CLIENT_PACKETS_SWAPITEMSPACKET_H
#define GD_CLIENT_PACKETS_SWAPITEMSPACKET_H

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
        class SwapItemsPacket : public gdn::Packet
        {
        private:
          unsigned int slot1;
          unsigned int slot2;

        public:
          SwapItemsPacket(unsigned int, unsigned int);
          SwapItemsPacket(const SwapItemsPacket&);
          SwapItemsPacket& operator=(const SwapItemsPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
