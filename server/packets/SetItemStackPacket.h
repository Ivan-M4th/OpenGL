#ifndef GD_SERVER_PACKETS_SETITEMSTACKPACKET_H
#define GD_SERVER_PACKETS_SETITEMSTACKPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

#include "../../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        class SetItemStackPacket : public gdn::Packet
        {
        private:
          unsigned int slot;
          const gdi::ItemStack* itemStack;

        public:
          SetItemStackPacket(unsigned int, const gdi::ItemStack*);
          SetItemStackPacket(const SetItemStackPacket&);
          SetItemStackPacket& operator=(const SetItemStackPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
