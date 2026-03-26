#include "PlayerDespawnPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        PlayerDespawnPacket::PlayerDespawnPacket(unsigned int clientId)
        {
          this->clientId = clientId;
        }

        PlayerDespawnPacket::PlayerDespawnPacket(PlayerDespawnPacket& packet)
        {
          clientId = packet.clientId;
        }

        PlayerDespawnPacket& PlayerDespawnPacket::operator=(const PlayerDespawnPacket& packet)
        {
          clientId = packet.clientId;
          return *this;
        }

        void PlayerDespawnPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::PLAYER_DESPAWN);
          writer.addSpace();
          writer.addData(clientId);
        }
      }
    }
  }
}
