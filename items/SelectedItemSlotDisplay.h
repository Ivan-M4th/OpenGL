#ifndef GD_ITEMS_SELECTEDITEMSLOTDISPLAY_H
#define GD_ITEMS_SELECTEDITEMSLOTDISPLAY_H

#include "../gddef.h"

#include "Inventory.h"

#include "../gui/GuiComponent.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class SelectedItemSlotDisplay : public gdgui::GuiComponent
      {
      protected:
        unsigned int index;
        Inventory* inventory;

      public:
        SelectedItemSlotDisplay();
        SelectedItemSlotDisplay(const SelectedItemSlotDisplay&);
        SelectedItemSlotDisplay& operator=(const SelectedItemSlotDisplay&);
        virtual ~SelectedItemSlotDisplay() override;

        bool isEmpty() const;
        bool setSlot(Inventory*, unsigned int);

        virtual void update(float) override;
        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
