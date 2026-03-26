#include "MainPlayerUpdatePacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        MainPlayerUpdatePacket::MainPlayerUpdatePacket(const gdco::MainPlayer* player)
        {
          this->player = player;
        }

        MainPlayerUpdatePacket::MainPlayerUpdatePacket(const MainPlayerUpdatePacket& packet)
        {
          player = packet.player;
        }

        MainPlayerUpdatePacket& MainPlayerUpdatePacket::operator=(const MainPlayerUpdatePacket& packet)
        {
          player = packet.player;
          return *this;
        }

        void MainPlayerUpdatePacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::MAIN_PLAYER_UPDATE);
          writer.addSpace();
          writer.addData(player->transformation.position);
          writer.addSpace();
          writer.addData(player->speed);
          writer.addSpace();
          writer.addData(player->transformation.rotation);
          writer.addSpace();
          writer.addData(player->rotationSpeed);
        }
      }
    }
  }
}
