#ifndef GD_SERVER_EVENTS_PACKETRECEIVEEVENT_H
#define GD_SERVER_EVENTS_PACKETRECEIVEEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../utils/BufferReader.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        class PacketReceiveEvent : public gde::Event
        {
        private:
          int clientId;
          gdu::BufferReader* reader;

        public:
          static unsigned int getStaticType();

          PacketReceiveEvent(int, gdu::BufferReader*);
          PacketReceiveEvent(const PacketReceiveEvent&);
          PacketReceiveEvent& operator=(const PacketReceiveEvent&);

          int getClientId() const;
          gdu::BufferReader* getReader() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
