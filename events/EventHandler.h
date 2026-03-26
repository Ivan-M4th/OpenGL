#ifndef GD_EVENTS_EVENTHANDLER_H
#define GD_EVENTS_EVENTHANDLER_H

#include "Event.h"
#include "AbstractListener.h"

#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      class EventHandler
      {
      private:
        ArrayList<AbstractListener*>* listeners;

        void deleteData();
      public:
        EventHandler();
        EventHandler(const EventHandler&);
        EventHandler& operator=(const EventHandler&);
        ~EventHandler();

        void registerListener(AbstractListener*);
        void onEvent(Event&);
      };
    }
  }
}

#endif
