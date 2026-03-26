#ifndef GD_ITEMS_INVENTORYITEMSLOT_H
#define GD_ITEMS_INVENTORYITEMSLOT_H

#include "../gddef.h"

#include "Inventory.h"

#include "../gui/GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      void addSelectedItemSlotDisplayToGui();

      class InventoryItemSlot : public gdgui::GuiComponent
      {
      protected:
        unsigned int index;
        Inventory* inventory;

      public:
        InventoryItemSlot();
        InventoryItemSlot(const gdm::Vector2&);
        InventoryItemSlot(const InventoryItemSlot&);
        InventoryItemSlot& operator=(const InventoryItemSlot&);
        virtual ~InventoryItemSlot() override;

        void setItem(Inventory*, unsigned int);

        virtual void render(const gdm::Vector2&) const override;
        virtual void onLeftClick() override;
      };
    }
  }
}

#endif
