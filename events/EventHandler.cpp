#include "EventHandler.h"

#include <cassert>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      EventHandler::EventHandler()
      {
        listeners = new ArrayList<AbstractListener*>[EVENT_AMOUNT];
      }

      EventHandler::EventHandler(const EventHandler& handler)
      {
        listeners = new ArrayList<AbstractListener*>[EVENT_AMOUNT];
        for(unsigned int i=0;i<EVENT_AMOUNT;i++)
        {
          *(listeners + i) = *(handler.listeners + i);
        }
      }

      EventHandler& EventHandler::operator=(const EventHandler& handler)
      {
        deleteData();
        listeners = new ArrayList<AbstractListener*>[EVENT_AMOUNT];
        for(unsigned int i=0;i<EVENT_AMOUNT;i++)
        {
          *(listeners + i) = *(handler.listeners + i);
        }
        return *this;
      }

      EventHandler::~EventHandler()
      {
        deleteData();
      }

      void EventHandler::deleteData()
      {
        delete[] listeners;
      }

      void EventHandler::registerListener(AbstractListener* listener)
      {
        unsigned int id = listener->getEventType();
        assert(id < EVENT_AMOUNT && "Event type is out of bounds!");
        if(!(listeners + id)->contains(listener))
        {
          std::cout << "registering listener of id: " << id << std::endl;
          (listeners + id)->add(listener);
        }
      }

      void EventHandler::onEvent(Event& event)
      {
        unsigned int id = event.getType();
        assert(id < EVENT_AMOUNT && "Event type is out of bounds!");

        for(unsigned int i=0;i<(listeners + id)->size();i++)
        {
          (*(listeners + id))[i]->onEvent(&event);
        }
      }
    }
  }
}
