#include "PlayerUpdatePacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        PlayerUpdatePacket::PlayerUpdatePacket(unsigned int clientId, const gdso::Player* player)
        {
          this->clientId = clientId;
          this->player = player;
        }

        PlayerUpdatePacket::PlayerUpdatePacket(const PlayerUpdatePacket& packet)
        {
          clientId = packet.clientId;
          player = packet.player;
        }

        PlayerUpdatePacket& PlayerUpdatePacket::operator=(const PlayerUpdatePacket& packet)
        {
          clientId = packet.clientId;
          player = packet.player;
          return *this;
        }

        void PlayerUpdatePacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::PLAYER_UPDATE);
          writer.addSpace();
          writer.addData(clientId);
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
