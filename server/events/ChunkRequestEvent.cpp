#include "ChunkRequestEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        unsigned int ChunkRequestEvent::getStaticType()
        {
          return gde::SERVER_CHUNK_REQUEST_EVENT;
        }

        ChunkRequestEvent::ChunkRequestEvent(unsigned int clientId, int cx, int cy, int cz)
        {
          this->clientId = clientId;
          this->cx = cx;
          this->cy = cy;
          this->cz = cz;
        }

        ChunkRequestEvent::ChunkRequestEvent(const ChunkRequestEvent& event)
        {
          clientId = event.clientId;
          cx = event.cx;
          cy = event.cy;
          cz = event.cz;
        }

        ChunkRequestEvent& ChunkRequestEvent::operator=(const ChunkRequestEvent& event)
        {
          clientId = event.clientId;
          cx = event.cx;
          cy = event.cy;
          cz = event.cz;
          return *this;
        }

        unsigned int ChunkRequestEvent::getClientId() const
        {
          return clientId;
        }

        int ChunkRequestEvent::getCX() const
        {
          return cx;
        }

        int ChunkRequestEvent::getCY() const
        {
          return cy;
        }

        int ChunkRequestEvent::getCZ() const
        {
          return cz;
        }

        unsigned int ChunkRequestEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
