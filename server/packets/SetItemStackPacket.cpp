#include "SetItemStackPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        SetItemStackPacket::SetItemStackPacket(unsigned int slot, const gdi::ItemStack* itemStack)
        {
          this->slot = slot;
          this->itemStack = itemStack;
        }

        SetItemStackPacket::SetItemStackPacket(const SetItemStackPacket& packet)
        {
          slot = packet.slot;
          itemStack = packet.itemStack;
        }

        SetItemStackPacket& SetItemStackPacket::operator=(const SetItemStackPacket& packet)
        {
          slot = packet.slot;
          itemStack = packet.itemStack;
          return *this;
        }

        void SetItemStackPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::INVENTORY_INFO);
          writer.addSpace();
          writer.addData(gdn::SET_ITEM);
          writer.addSpace();
          writer.addData(slot);
          writer.addSpace();
          writer.addData(itemStack);
        }
      }
    }
  }
}
