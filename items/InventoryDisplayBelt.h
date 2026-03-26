#ifndef GD_ITEMS_INVENTORYDISPLAYBELT_H
#define GD_ITEMS_INVENTORYDISPLAYBELT_H

#include "../gddef.h"

#include "Inventory.h"
#include "InventoryItemDisplay.h"

#include "../utils/ArrayList.h"

#include "../gui/GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class InventoryDisplayBelt : public gdgui::GuiComponent
      {
      protected:
        unsigned int index;
        Inventory* inventory;

        unsigned int nextIndex;
        float beltPosition;
        float speed;
        ArrayList<InventoryItemDisplay> displays;

        gdm::Vector2 getCenter() const;
        int getDifference(unsigned int) const;
        void updateDisplay(unsigned int, const gdm::Vector2&);
        void updateDisplays();
        void buildDisplays();
      public:
        InventoryDisplayBelt(const gdm::Vector2&, const gdm::Vector2&);
        InventoryDisplayBelt(const InventoryDisplayBelt&);
        InventoryDisplayBelt& operator=(const InventoryDisplayBelt&);
        virtual ~InventoryDisplayBelt() override;

        void setInventory(Inventory*);
        void next();
        void previous();
        unsigned int getSelectedSlot() const;

        virtual void update(float) override;
        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
