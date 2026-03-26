#include "ClientDisconnectEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        unsigned int ClientDisconnectEvent::getStaticType()
        {
          return gde::SERVER_PLAYER_DISCONNECT_EVENT;
        }

        ClientDisconnectEvent::ClientDisconnectEvent(unsigned int clientId)
        {
          this->clientId = clientId;
        }

        ClientDisconnectEvent::ClientDisconnectEvent(const ClientDisconnectEvent& event)
        {
          clientId = event.clientId;
        }

        ClientDisconnectEvent& ClientDisconnectEvent::operator=(const ClientDisconnectEvent& event)
        {
          clientId = event.clientId;
          return *this;
        }

        unsigned int ClientDisconnectEvent::getClientId() const
        {
          return clientId;
        }

        unsigned int ClientDisconnectEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
