#include "InventoryItemSlot.h"

#include "SelectedItemSlotDisplay.h"

#include "../gui/Gui.h"
#include "../gui/GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      SelectedItemSlotDisplay SELECTED_ITEM_SLOT_DISPLAY;

      void addSelectedItemSlotDisplayToGui()
      {
        SELECTED_ITEM_SLOT_DISPLAY = SelectedItemSlotDisplay();
        gdgui::addGuiComponent(&SELECTED_ITEM_SLOT_DISPLAY);
      }

      InventoryItemSlot::InventoryItemSlot() : gdgui::GuiComponent(gdm::Vector2(), gdm::Vector2(0.052, 0.093))
      {
        index = 0;
        inventory = NULL;
      }

      InventoryItemSlot::InventoryItemSlot(const gdm::Vector2& relativePosition) : gdgui::GuiComponent(relativePosition, gdm::Vector2(0.052, 0.093))
      {
        index = 0;
        inventory = NULL;
      }

      InventoryItemSlot::InventoryItemSlot(const InventoryItemSlot& slot) : gdgui::GuiComponent(slot)
      {
        index = slot.index;
        inventory = slot.inventory;
      }

      InventoryItemSlot& InventoryItemSlot::operator=(const InventoryItemSlot& slot)
      {
        gdgui::GuiComponent::operator=(slot);
        index = slot.index;
        inventory = slot.inventory;
        return *this;
      }

      InventoryItemSlot::~InventoryItemSlot()
      {

      }

      void InventoryItemSlot::setItem(Inventory* inventory, unsigned int index)
      {
        this->index = index;
        this->inventory = inventory;
      }

      void InventoryItemSlot::render(const gdm::Vector2& referencePosition) const
      {
        gdgui::setColor(0.0, 0.0, 0.0, 0.5);
        gdgui::renderColoredQuad(referencePosition + position + gdm::Vector2(0.005, 0.007), size);
        gdgui::setColor(0.1835, 0.281, 0.32, 1.0);
        gdgui::renderColoredQuad(referencePosition + position, size);
        if(inventory != NULL && !inventory->getItemStack(index)->isEmpty())
        {
          unsigned int itemIndex = inventory->getItemStack(index)->getItemId();
          gdgui::renderItemIcon(itemIndex, referencePosition + position, size);
        }

        gdgui::GuiComponent::render(referencePosition);

        if(gdgui::HOVERED_COMPONENT == this)
        {
          gdgui::renderHoveredBox(referencePosition + position, size);
        }
        else if(gdgui::ACTIVE_COMPONENT == this)
        {
          gdgui::renderHoveredBox(referencePosition + position, size);
        }
      }

      void InventoryItemSlot::onLeftClick()
      {
        if(!SELECTED_ITEM_SLOT_DISPLAY.setSlot(inventory, index))
        {
          gdgui::ACTIVE_COMPONENT = NULL;
        }
      }
    }
  }
}
