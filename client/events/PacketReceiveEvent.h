#ifndef GD_CLIENT_EVENTS_PACKETRECEIVEEVENT_H
#define GD_CLIENT_EVENTS_PACKETRECEIVEEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../utils/BufferReader.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class PacketReceiveEvent : public gde::Event
        {
        private:
          gdu::BufferReader* reader;

        public:
          static unsigned int getStaticType();

          PacketReceiveEvent(gdu::BufferReader*);
          PacketReceiveEvent(const PacketReceiveEvent&);
          PacketReceiveEvent& operator=(const PacketReceiveEvent&);

          gdu::BufferReader* getReader() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
