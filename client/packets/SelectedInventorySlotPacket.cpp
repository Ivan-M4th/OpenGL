#include "SelectedInventorySlotPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        SelectedInventorySlotPacket::SelectedInventorySlotPacket(unsigned int slot)
        {
          this->slot = slot;
        }

        SelectedInventorySlotPacket::SelectedInventorySlotPacket(const SelectedInventorySlotPacket& packet)
        {
          slot = packet.slot;
        }

        SelectedInventorySlotPacket& SelectedInventorySlotPacket::operator=(const SelectedInventorySlotPacket& packet)
        {
          slot = packet.slot;
          return *this;
        }

        void SelectedInventorySlotPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::INVENTORY_INFO);
          writer.addSpace();
          writer.addData(gdn::SELECTED_INVENTORY_SLOT);
          writer.addSpace();
          writer.addData(slot);
        }
      }
    }
  }
}
