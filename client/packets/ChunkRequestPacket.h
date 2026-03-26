#ifndef GD_CLIENT_PACKETS_CHUNKREQUESTPACKET_H
#define GD_CLIENT_PACKETS_CHUNKREQUESTPACKET_H

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
        class ChunkRequestPacket : public gdn::Packet
        {
        private:
          int cx;
          int cy;
          int cz;

        public:
          ChunkRequestPacket(int, int, int);
          ChunkRequestPacket(const ChunkRequestPacket&);
          ChunkRequestPacket& operator=(const ChunkRequestPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
