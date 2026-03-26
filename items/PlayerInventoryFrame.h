#ifndef GD_ITEMS_PLAYERINVENTORYFRAME_H
#define GD_ITEMS_PLAYERINVENTORYFRAME_H

#include "../gddef.h"

#include "Inventory.h"
#include "InventoryFrame.h"

#include "../gui/GuiComponent.h"
#include "../gui/Panel.h"

#include "../math/Vector2.h"

#include "../text/Text.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class PlayerInventoryFrame : public gdgui::GuiComponent
      {
      protected:
        gdgui::Panel panel;
        InventoryFrame* inventoryFrames;
        gdt::Text title;

      public:
        PlayerInventoryFrame();
        PlayerInventoryFrame(const PlayerInventoryFrame&);
        PlayerInventoryFrame& operator=(const PlayerInventoryFrame&);
        virtual ~PlayerInventoryFrame() override;

        void setInventories(Inventory*);

        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
