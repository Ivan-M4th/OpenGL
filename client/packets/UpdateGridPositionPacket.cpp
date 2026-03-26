#include "UpdateGridPositionPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        UpdateGridPositionPacket::UpdateGridPositionPacket(const gdm::Vector3i& position)
        {
          this->position = position;
        }

        UpdateGridPositionPacket::UpdateGridPositionPacket(const UpdateGridPositionPacket& packet)
        {
          position = packet.position;
        }

        UpdateGridPositionPacket& UpdateGridPositionPacket::operator=(const UpdateGridPositionPacket& packet)
        {
          position = packet.position;
          return *this;
        }

        void UpdateGridPositionPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::TERRAIN_INFO);
          writer.addSpace();
          writer.addData(gdn::UPDATE_GRID_POSITION);
          writer.addSpace();
          writer.addData(position);
        }
      }
    }
  }
}
