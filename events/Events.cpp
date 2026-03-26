#include "Events.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      EventHandler* mainEventHandler = NULL;

      void createMainEventHandler()
      {
        mainEventHandler = new EventHandler();
      }

      void deleteMainEventHandler()
      {
        delete mainEventHandler;
        mainEventHandler = NULL;
      }

      EventHandler* getMainEventHandler()
      {
        return mainEventHandler;
      }

      void registerListener(AbstractListener* listener)
      {
        if(mainEventHandler != NULL)
        {
          mainEventHandler->registerListener(listener);
        }
      }

      void onEvent(Event& event)
      {
        if(mainEventHandler != NULL)
        {
          mainEventHandler->onEvent(event);
        }
      }
    }
  }
}
