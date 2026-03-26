#include "InventoryItemDisplay.h"

#include "../gui/Gui.h"
#include "../gui/GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      InventoryItemDisplay::InventoryItemDisplay() : gdgui::GuiComponent(gdm::Vector2(), gdm::Vector2(0.052, 0.093))
      {
        index = 0;
        inventory = NULL;
      }

      InventoryItemDisplay::InventoryItemDisplay(const InventoryItemDisplay& display) : gdgui::GuiComponent(display)
      {
        index = display.index;
        inventory = display.inventory;
      }

      InventoryItemDisplay& InventoryItemDisplay::operator=(const InventoryItemDisplay& display)
      {
        gdgui::GuiComponent::operator=(display);
        index = display.index;
        inventory = display.inventory;
        return *this;
      }

      InventoryItemDisplay::~InventoryItemDisplay()
      {

      }

      void InventoryItemDisplay::setItem(Inventory* inventory, unsigned int index)
      {
        this->inventory = inventory;
        this->index = index;
      }

      void InventoryItemDisplay::clear()
      {
        setItem(NULL, 0);
      }

      bool InventoryItemDisplay::isEmpty() const
      {
        if(inventory == NULL)
        {
          return true;
        }

        return inventory->getItemStack(index)->isEmpty();
      }

      unsigned int InventoryItemDisplay::getIndex() const
      {
        return index;
      }

      Inventory* InventoryItemDisplay::getInventory() const
      {
        return inventory;
      }

      void InventoryItemDisplay::render(const gdm::Vector2& referencePosition) const
      {
        gdgui::setColor(0.0, 0.0, 0.0, 0.5);
        gdgui::renderColoredQuad(referencePosition + position + gdm::Vector2(0.005, 0.007), size);
        gdgui::setColor(0.160, 0.4375, 0.550, 1.0);
        gdgui::renderColoredQuad(referencePosition + position, size);
        if(inventory != NULL && !inventory->getItemStack(index)->isEmpty())
        {
          unsigned int itemIndex = inventory->getItemStack(index)->getItemId();
          gdgui::renderItemIcon(itemIndex, referencePosition + position, size);
        }
        gdgui::GuiComponent::render(referencePosition);
      }
    }
  }
}
