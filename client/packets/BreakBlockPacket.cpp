#include "BreakBlockPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        BreakBlockPacket::BreakBlockPacket(int bx, int by, int bz)
        {
          this->bx = bx;
          this->by = by;
          this->bz = bz;
        }

        BreakBlockPacket::BreakBlockPacket(const BreakBlockPacket& packet)
        {
          bx = packet.bx;
          by = packet.by;
          bz = packet.bz;
        }

        BreakBlockPacket& BreakBlockPacket::operator=(const BreakBlockPacket& packet)
        {
          bx = packet.bx;
          by = packet.by;
          bz = packet.bz;
          return *this;
        }

        void BreakBlockPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::TERRAIN_INFO);
          writer.addSpace();
          writer.addData(gdn::BREAK_BLOCK);
          writer.addSpace();
          writer.addData(bx);
          writer.addSpace();
          writer.addData(by);
          writer.addSpace();
          writer.addData(bz);
        }
      }
    }
  }
}
