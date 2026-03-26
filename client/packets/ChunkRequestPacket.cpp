#include "ChunkRequestPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        ChunkRequestPacket::ChunkRequestPacket(int cx, int cy, int cz)
        {
          this->cx = cx;
          this->cy = cy;
          this->cz = cz;
        }

        ChunkRequestPacket::ChunkRequestPacket(const ChunkRequestPacket& packet)
        {
          cx = packet.cx;
          cy = packet.cy;
          cz = packet.cz;
        }

        ChunkRequestPacket& ChunkRequestPacket::operator=(const ChunkRequestPacket& packet)
        {
          cx = packet.cx;
          cy = packet.cy;
          cz = packet.cz;
          return *this;
        }

        void ChunkRequestPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::TERRAIN_INFO);
          writer.addSpace();
          writer.addData(gdn::DOWNLOAD_CHUNK);
          writer.addSpace();
          writer.addData(cx);
          writer.addSpace();
          writer.addData(cy);
          writer.addSpace();
          writer.addData(cz);
        }
      }
    }
  }
}
