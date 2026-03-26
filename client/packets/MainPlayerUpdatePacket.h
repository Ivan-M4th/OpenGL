#ifndef GD_CLIENT_PACKETS_MAINPLAYERUPDATEPACKET_H
#define GD_CLIENT_PACKETS_MAINPLAYERUPDATEPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

#include "../objects/MainPlayer.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        class MainPlayerUpdatePacket : public gdn::Packet
        {
        private:
          const gdco::MainPlayer* player;

        public:
          MainPlayerUpdatePacket(const gdco::MainPlayer*);
          MainPlayerUpdatePacket(const MainPlayerUpdatePacket&);
          MainPlayerUpdatePacket& operator=(const MainPlayerUpdatePacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
