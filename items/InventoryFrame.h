#ifndef GD_ITEMS_INVENTORYFRAME_H
#define GD_ITEMS_INVENTORYFRAME_H

#include "../gddef.h"

#include "InventoryItemSlot.h"
#include "Inventory.h"

#include "../gui/GuiComponent.h"
#include "../gui/TextArea.h"

#include "../utils/ArrayList.h"

#include "../math/Vector2.h"

#include "../text/Font.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class InventoryFrame : public gdgui::GuiComponent
      {
      protected:
        gdgui::TextArea title;

        Inventory* inventory;
        ArrayList<InventoryItemSlot> slots;

        void createItemSlots();
      public:
        InventoryFrame();
        InventoryFrame(const InventoryFrame&);
        InventoryFrame& operator=(const InventoryFrame&);
        virtual ~InventoryFrame() override;

        void clear();
        void setWidth(float);
        void setInventory(Inventory*);

        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
