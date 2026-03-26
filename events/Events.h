#ifndef GD_EVENTS_EVENTS_H
#define GD_EVENTS_EVENTS_H

#include "EventHandler.h"
#include "AbstractListener.h"
#include "Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      void createMainEventHandler();
      void deleteMainEventHandler();
      EventHandler* getMainEventHandler();
      void registerListener(AbstractListener*);
      void onEvent(Event&);
    }
  }
}

#endif
