#include "MainPlayerSwapItemStacksListener.h"

#include "../packets/SwapItemsPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        MainPlayerSwapItemStacksListener::MainPlayerSwapItemStacksListener(gdn::Client* client)
        {
          this->client = client;
        }

        MainPlayerSwapItemStacksListener::MainPlayerSwapItemStacksListener(const MainPlayerSwapItemStacksListener& listener)
        {
          client = listener.client;
        }

        MainPlayerSwapItemStacksListener& MainPlayerSwapItemStacksListener::operator=(const MainPlayerSwapItemStacksListener& listener)
        {
          client = listener.client;
          return *this;
        }

        void MainPlayerSwapItemStacksListener::onEvent(gdce::MainPlayerSwapItemStacksEvent* event)
        {
          client->sendPacket(gdcp::SwapItemsPacket(event->getIndex1(), event->getIndex2()));
        }
      }
    }
  }
}
