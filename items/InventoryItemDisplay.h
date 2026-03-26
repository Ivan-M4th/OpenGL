#ifndef GD_ITEMS_INVENTORYITEMDISPLAY_H
#define GD_ITEMS_INVENTORYITEMDISPLAY_H

#include "../gddef.h"

#include "Inventory.h"

#include "../gui/GuiComponent.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class InventoryItemDisplay : public gdgui::GuiComponent
      {
      protected:
        unsigned int index;
        Inventory* inventory;

      public:
        InventoryItemDisplay();
        InventoryItemDisplay(const InventoryItemDisplay&);
        InventoryItemDisplay& operator=(const InventoryItemDisplay&);
        virtual ~InventoryItemDisplay() override;

        void setItem(Inventory*, unsigned int);
        void clear();
        bool isEmpty() const;
        unsigned int getIndex() const;
        Inventory* getInventory() const;

        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
