#include "PacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        unsigned int PacketReceiveEvent::getStaticType()
        {
          return gde::SERVER_PACKET_RECEIVE;
        }

        PacketReceiveEvent::PacketReceiveEvent(int clientId, gdu::BufferReader* reader)
        {
          this->clientId = clientId;
          this->reader = reader;
        }

        PacketReceiveEvent::PacketReceiveEvent(const PacketReceiveEvent& event)
        {
          clientId = event.clientId;
          reader = event.reader;
        }

        PacketReceiveEvent& PacketReceiveEvent::operator=(const PacketReceiveEvent& event)
        {
          clientId = event.clientId;
          reader = event.reader;
          return *this;
        }

        int PacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        gdu::BufferReader* PacketReceiveEvent::getReader() const
        {
          return reader;
        }

        unsigned int PacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
