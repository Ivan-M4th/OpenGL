#include "PlayerPlayActionPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        PlayerPlayActionPacket::PlayerPlayActionPacket(unsigned int clientId, unsigned int actionId)
        {
          this->clientId = clientId;
          this->actionId = actionId;
        }

        PlayerPlayActionPacket::PlayerPlayActionPacket(const PlayerPlayActionPacket& packet)
        {
          clientId = packet.clientId;
          actionId = packet.actionId;
        }

        PlayerPlayActionPacket& PlayerPlayActionPacket::operator=(const PlayerPlayActionPacket& packet)
        {
          clientId = packet.clientId;
          actionId = packet.actionId;
          return *this;
        }

        void PlayerPlayActionPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::GAME_INFO);
          writer.addSpace();
          writer.addData(gdn::PLAYER_PLAY_ACTION);
          writer.addSpace();
          writer.addData(clientId);
          writer.addSpace();
          writer.addData(actionId);
        }
      }
    }
  }
}
