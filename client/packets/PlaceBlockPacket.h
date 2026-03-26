#ifndef GD_CLIENT_PACKETS_PLACEBLOCKPACKET_H
#define GD_CLIENT_PACKETS_PLACEBLOCKPACKET_H

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
        class PlaceBlockPacket : public gdn::Packet
        {
        private:
          int bx;
          int by;
          int bz;
          unsigned int materialId;

        public:
          PlaceBlockPacket(int, int, int, unsigned int);
          PlaceBlockPacket(const PlaceBlockPacket&);
          PlaceBlockPacket& operator=(const PlaceBlockPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
