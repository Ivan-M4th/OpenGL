#include "PlaceBlockPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        PlaceBlockPacket::PlaceBlockPacket(int bx, int by, int bz, unsigned int materialId)
        {
          this->bx = bx;
          this->by = by;
          this->bz = bz;
          this->materialId = materialId;
        }

        PlaceBlockPacket::PlaceBlockPacket(const PlaceBlockPacket& packet)
        {
          bx = packet.bx;
          by = packet.by;
          bz = packet.bz;
          materialId = packet.materialId;
        }

        PlaceBlockPacket& PlaceBlockPacket::operator=(const PlaceBlockPacket& packet)
        {
          bx = packet.bx;
          by = packet.by;
          bz = packet.bz;
          materialId = packet.materialId;
          return *this;
        }

        void PlaceBlockPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::TERRAIN_INFO);
          writer.addSpace();
          writer.addData(gdn::PLACE_BLOCK);
          writer.addSpace();
          writer.addData(bx);
          writer.addSpace();
          writer.addData(by);
          writer.addSpace();
          writer.addData(bz);
          writer.addSpace();
          writer.addData(materialId);
        }
      }
    }
  }
}
