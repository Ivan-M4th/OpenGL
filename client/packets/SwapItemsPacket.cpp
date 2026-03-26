#include "SwapItemsPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        SwapItemsPacket::SwapItemsPacket(unsigned int slot1, unsigned int slot2)
        {
          this->slot1 = slot1;
          this->slot2 = slot2;
        }

        SwapItemsPacket::SwapItemsPacket(const SwapItemsPacket& packet)
        {
          slot1 = packet.slot1;
          slot2 = packet.slot2;
        }

        SwapItemsPacket& SwapItemsPacket::operator=(const SwapItemsPacket& packet)
        {
          slot1 = packet.slot1;
          slot2 = packet.slot2;
          return *this;
        }

        void SwapItemsPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::INVENTORY_INFO);
          writer.addSpace();
          writer.addData(gdn::SWAP_ITEMS);
          writer.addSpace();
          writer.addData(slot1);
          writer.addSpace();
          writer.addData(slot2);
        }
      }
    }
  }
}
