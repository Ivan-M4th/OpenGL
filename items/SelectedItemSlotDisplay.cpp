#include "SelectedItemSlotDisplay.h"

#include "ItemStack.h"

#include "../gui/Gui.h"
#include "../gui/GuiRendering.h"

#include "../events/Events.h"
#include "../client/events/MainPlayerSwapItemStacksEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      SelectedItemSlotDisplay::SelectedItemSlotDisplay() : gdgui::GuiComponent(gdm::Vector2(), gdm::Vector2(0.052, 0.093))
      {
        index = 0;
        inventory = NULL;
        hoverable = false;
      }

      SelectedItemSlotDisplay::SelectedItemSlotDisplay(const SelectedItemSlotDisplay& display) : gdgui::GuiComponent(display)
      {
        index = display.index;
        inventory = display.inventory;
      }

      SelectedItemSlotDisplay& SelectedItemSlotDisplay::operator=(const SelectedItemSlotDisplay& display)
      {
        gdgui::GuiComponent::operator=(display);
        index = display.index;
        inventory = display.inventory;
        return *this;
      }

      SelectedItemSlotDisplay::~SelectedItemSlotDisplay()
      {

      }

      bool SelectedItemSlotDisplay::isEmpty() const
      {
        if(inventory == NULL)
        {
          return true;
        }
        return inventory->getItemStack(index)->isEmpty();
      }

      bool SelectedItemSlotDisplay::setSlot(Inventory* inventory1, unsigned int index1)
      {
        if(inventory1 == NULL)
        {
          index = 0;
          inventory = NULL;
          return false;
        }

        if(isEmpty())
        {
          if(inventory1->getItemStack(index1)->isEmpty())
          {
            index = 0;
            inventory = NULL;
            return false;
          }
          else
          {
            index = index1;
            inventory = inventory1;
            return true;
          }
        }
        else
        {
          ItemStack itemStack1 = *inventory1->getItemStack(index1);
          inventory1->setItemStack(index1, *inventory->getItemStack(index));
          inventory->setItemStack(index, itemStack1);

          gdce::MainPlayerSwapItemStacksEvent event(index1, index);
          gde::onEvent(event);

          index = 0;
          inventory = NULL;
          return false;
        }
      }

      void SelectedItemSlotDisplay::update(float timePassed)
      {
        setPosition(gdm::Vector2(gdgui::MOUSE_X, gdgui::MOUSE_Y) - 0.5*size);
        GuiComponent::update(timePassed);
      }

      void SelectedItemSlotDisplay::render(const gdm::Vector2& referencePosition) const
      {
        if(inventory != NULL && !inventory->getItemStack(index)->isEmpty())
        {
          gdgui::setColor(0.0, 0.0, 0.0, 0.5);
          gdgui::renderColoredQuad(referencePosition + position + gdm::Vector2(0.005, 0.007), size);
          gdgui::setColor(0.160, 0.4375, 0.550, 1.0);
          gdgui::renderColoredQuad(referencePosition + position, size);
          unsigned int itemIndex = inventory->getItemStack(index)->getItemId();
          gdgui::renderItemIcon(itemIndex, referencePosition + position, size);
        }

        gdgui::GuiComponent::render(referencePosition);
      }
    }
  }
}
