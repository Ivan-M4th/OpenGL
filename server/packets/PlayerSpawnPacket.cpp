#include "PlayerSpawnPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        PlayerSpawnPacket::PlayerSpawnPacket(unsigned int clientId, gdso::Player* player)
        {
          this->clientId = clientId;
          this->player = player;
        }

        PlayerSpawnPacket::PlayerSpawnPacket(const PlayerSpawnPacket& packet)
        {
          clientId = packet.clientId;
          player = packet.player;
        }

        PlayerSpawnPacket& PlayerSpawnPacket::operator=(const PlayerSpawnPacket& packet)
        {
          clientId = packet.clientId;
          player = packet.player;
          return *this;
        }

        void PlayerSpawnPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::PLAYER_SPAWN);
          writer.addSpace();
          writer.addData(clientId);
          writer.addSpace();
          writer.addData(player->transformation.position);
          writer.addSpace();
          writer.addData(player->transformation.rotation);
        }
      }
    }
  }
}
