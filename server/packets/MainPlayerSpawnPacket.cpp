#include "MainPlayerSpawnPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        MainPlayerSpawnPacket::MainPlayerSpawnPacket(gdso::Player* player)
        {
          this->player = player;
        }

        MainPlayerSpawnPacket::MainPlayerSpawnPacket(MainPlayerSpawnPacket& packet)
        {
          player = packet.player;
        }

        MainPlayerSpawnPacket& MainPlayerSpawnPacket::operator=(const MainPlayerSpawnPacket& packet)
        {
          player = packet.player;
          return *this;
        }

        void MainPlayerSpawnPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::MAIN_PLAYER_SPAWN);
          writer.addSpace();
          writer.addData(player->transformation.position);
          writer.addSpace();
          writer.addData(player->transformation.rotation);
        }
      }
    }
  }
}
