#ifndef GD_CLIENT_EVENTS_MAINPLAYERSWAPITEMSTACKSEVENT_H
#define GD_CLIENT_EVENTS_MAINPLAYERSWAPITEMSTACKSEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class MainPlayerSwapItemStacksEvent : public gde::Event
        {
        private:
          unsigned int index1;
          unsigned int index2;

        public:
          static unsigned int getStaticType();

          MainPlayerSwapItemStacksEvent(unsigned int, unsigned int);
          MainPlayerSwapItemStacksEvent(const MainPlayerSwapItemStacksEvent&);
          MainPlayerSwapItemStacksEvent& operator=(const MainPlayerSwapItemStacksEvent&);

          unsigned int getIndex1() const;
          unsigned int getIndex2() const;

          virtual unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
