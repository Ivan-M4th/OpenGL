#ifndef GD_CLIENT_LISTENERS_MAINPLAYERSWAPITEMSTACKSLISTENER_H
#define GD_CLIENT_LISTENERS_MAINPLAYERSWAPITEMSTACKSLISTENER_H

#include "../../gddef.h"

#include "../events/MainPlayerSwapItemStacksEvent.h"

#include "../../events/Listener.h"

#include "../../networking/Client.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class MainPlayerSwapItemStacksListener : public gde::Listener<gdce::MainPlayerSwapItemStacksEvent>
        {
        private:
          gdn::Client* client;

        public:
          MainPlayerSwapItemStacksListener(gdn::Client*);
          MainPlayerSwapItemStacksListener(const MainPlayerSwapItemStacksListener&);
          MainPlayerSwapItemStacksListener& operator=(const MainPlayerSwapItemStacksListener&);

          void onEvent(gdce::MainPlayerSwapItemStacksEvent*) override;
        };
      }
    }
  }
}

#endif
