#include "ConnectionPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace packets
      {
        ConnectionPacket::ConnectionPacket(unsigned int maxPlayers)
        {
          this->maxPlayers = maxPlayers;
        }

        ConnectionPacket::ConnectionPacket(const ConnectionPacket& packet)
        {
          maxPlayers = packet.maxPlayers;
        }

        ConnectionPacket& ConnectionPacket::operator=(const ConnectionPacket& packet)
        {
          maxPlayers = packet.maxPlayers;
          return *this;
        }

        void ConnectionPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::CONNECTION);
          writer.addSpace();
          writer.addData(gdn::SERVER_INFO);
          writer.addSpace();
          writer.addData(maxPlayers);
        }
      }
    }
  }
}
