#ifndef GD_CLIENT_LISTENERS_MAINPLAYERSETITEMSTACKLISTENER_H
#define GD_CLIENT_LISTENERS_MAINPLAYERSETITEMSTACKLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/MainPlayerSetItemStackEvent.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class MainPlayerSetItemStackListener : public gde::Listener<gdce::MainPlayerSetItemStackEvent>
        {
        private:
          Players* players;

        public:
          MainPlayerSetItemStackListener(Players*);
          MainPlayerSetItemStackListener(const MainPlayerSetItemStackListener&);
          MainPlayerSetItemStackListener& operator=(const MainPlayerSetItemStackListener&);

          void onEvent(gdce::MainPlayerSetItemStackEvent*) override;
        };
      }
    }
  }
}

#endif
