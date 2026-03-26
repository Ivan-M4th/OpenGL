#ifndef GD_SERVER_PACKETS_MAINPLAYERSPAWNPACKET_H
#define GD_SERVER_PACKETS_MAINPLAYERSPAWNPACKET_H

#include "../../gddef.h"

#include "../../networking/Packet.h"

#include "../objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        class MainPlayerSpawnPacket : public gdn::Packet
        {
        private:
          gdso::Player* player;

        public:
          MainPlayerSpawnPacket(gdso::Player*);
          MainPlayerSpawnPacket(MainPlayerSpawnPacket&);
          MainPlayerSpawnPacket& operator=(const MainPlayerSpawnPacket&);

          void loadToBuffer(const gdu::BufferWriter&) const override;
        };
      }
    }
  }
}

#endif
