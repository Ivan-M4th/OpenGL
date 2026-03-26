#ifndef GD_CLIENT_PACKETS_SWAPITEMSPACKET_H
#define GD_CLIENT_PACKETS_SWAPITEMSPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

#include "../../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        class UpdateGridPositionPacket : public gdn::Packet
        {
        private:
          gdm::Vector3i position;

        public:
          UpdateGridPositionPacket(const gdm::Vector3i&);
          UpdateGridPositionPacket(const UpdateGridPositionPacket&);
          UpdateGridPositionPacket& operator=(const UpdateGridPositionPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
