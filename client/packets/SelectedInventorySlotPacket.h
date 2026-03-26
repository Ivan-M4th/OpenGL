#ifndef GD_CLIENT_PACKETS_SELECTEDINVENTORYSLOTPACKET_H
#define GD_CLIENT_PACKETS_SELECTEDINVENTORYSLOTPACKET_H

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
        class SelectedInventorySlotPacket : public gdn::Packet
        {
        private:
          unsigned int slot;

        public:
          SelectedInventorySlotPacket(unsigned int);
          SelectedInventorySlotPacket(const SelectedInventorySlotPacket&);
          SelectedInventorySlotPacket& operator=(const SelectedInventorySlotPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
