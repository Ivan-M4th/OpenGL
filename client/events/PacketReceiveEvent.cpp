#include "PacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int PacketReceiveEvent::getStaticType()
        {
          return gde::CLIENT_PACKET_RECEIVE;
        }

        PacketReceiveEvent::PacketReceiveEvent(gdu::BufferReader* reader)
        {
          this->reader = reader;
        }

        PacketReceiveEvent::PacketReceiveEvent(const PacketReceiveEvent& event)
        {
          reader = event.reader;
        }

        PacketReceiveEvent& PacketReceiveEvent::operator=(const PacketReceiveEvent& event)
        {
          reader = event.reader;
          return *this;
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
