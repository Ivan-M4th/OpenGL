#ifndef GD_CLIENT_EVENTS_MAINPLAYERSETITEMSTACKEVENT_H
#define GD_CLIENT_EVENTS_MAINPLAYERSETITEMSTACKEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class MainPlayerSetItemStackEvent : public gde::Event
        {
        private:
          unsigned int slot;
          const gdi::ItemStack* itemStack;

        public:
          static unsigned int getStaticType();

          MainPlayerSetItemStackEvent(unsigned int, const gdi::ItemStack*);
          MainPlayerSetItemStackEvent(const MainPlayerSetItemStackEvent&);
          MainPlayerSetItemStackEvent& operator=(const MainPlayerSetItemStackEvent&);

          unsigned int getSlot() const;
          const gdi::ItemStack* getItemStack() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
