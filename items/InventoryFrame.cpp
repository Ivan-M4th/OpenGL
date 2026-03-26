#include "InventoryFrame.h"

#include "../utils/String.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {

      const float SLOT_SPACING = 0.035;

      InventoryFrame::InventoryFrame() : gdgui::GuiComponent(gdm::Vector2(), gdm::Vector2())
      {
        inventory = NULL;
      }

      InventoryFrame::InventoryFrame(const InventoryFrame& frame) : gdgui::GuiComponent(frame), title(frame.title)
      {
        components.clear();
        addComponent(&title);
        inventory = frame.inventory;

        createItemSlots();
      }

      InventoryFrame& InventoryFrame::operator=(const InventoryFrame& frame)
      {
        gdgui::GuiComponent::operator=(frame);

        components.clear();
        title = frame.title;
        addComponent(&title);

        inventory = frame.inventory;
        createItemSlots();
        return *this;
      }

      InventoryFrame::~InventoryFrame()
      {

      }

      void InventoryFrame::createItemSlots()
      {
        clear();
        if(inventory == NULL || inventory->getSize() == 0)
        {
          return;
        }

        slots.setSize(inventory->getSize());

        float slotSpace = slots[0].getSize().x;
        float slotHeight = slots[0].getSize().y + SLOT_SPACING;
        float slotsSpace = (float)(inventory->getWidth())*slotSpace;
        float freeSpace = size.x - slotsSpace;
        float space = freeSpace/(float)(inventory->getWidth() - 1);

        unsigned int amount = 0;
        float sy = title.getSize().y + SLOT_SPACING;
        for(unsigned int i=0;i<inventory->getSize();i++)
        {
          if(amount >= inventory->getWidth())
          {
            amount = 0;
            sy+=slotHeight;
          }

          float sx = amount*(space + slotSpace);
          slots[i].setPosition(gdm::Vector2(sx, sy));
          slots[i].setItem(inventory, i);
          addComponent(&slots[i]);

          amount++;
        }
        sy+=slotHeight;
        setSize(gdm::Vector2(size.x, sy));
      }

      void InventoryFrame::clear()
      {
        components.clear();
        slots.clear();
        addComponent(&title);
      }

      void InventoryFrame::setWidth(float width)
      {
        title.setPosition(gdm::Vector2(0.0, 0.0));
        title.setSize(gdm::Vector2(width, 0.06));
        title.setTextColor(gdm::Vector3(1.0, 1.0, 1.0));
        title.setTextCentered(true);
        title.setTextSize(0.11);
        title.setText(gdu::String("Items In Hands"));
        setSize(gdm::Vector2(width, title.getSize().y));
      }

      void InventoryFrame::setInventory(Inventory* inventory)
      {
        this->inventory = inventory;
        createItemSlots();
      }

      void InventoryFrame::render(const gdm::Vector2& referencePosition) const
      {
        renderChildren(referencePosition);
      }
    }
  }
}
