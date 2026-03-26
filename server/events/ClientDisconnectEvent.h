#ifndef GD_SERVER_EVENTS_CLIENTDISCONNECTEVENT_H
#define GD_SERVER_EVENTS_CLIENTDISCONNECTEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        class ClientDisconnectEvent : public gde::Event
        {
        private:
          unsigned int clientId;

        public:
          static unsigned int getStaticType();

          ClientDisconnectEvent(unsigned int);
          ClientDisconnectEvent(const ClientDisconnectEvent&);
          ClientDisconnectEvent& operator=(const ClientDisconnectEvent&);

          unsigned int getClientId() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
