#include "PlayerInventoryFrame.h"

#include "../gui/Gui.h"
#include "../gui/GuiRendering.h"

#include "../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      const unsigned int INVENTORY_FRAMES_AMOUNT = 1;

      PlayerInventoryFrame::PlayerInventoryFrame() : gdgui::GuiComponent(gdm::Vector2(0.51, 0.2), gdm::Vector2(0.46, 0.6))
      {
        inventoryFrames = new InventoryFrame[INVENTORY_FRAMES_AMOUNT];
        addComponent(&panel);
        title.size = 0.15;
        title.color = gdm::Vector3(1.0, 1.0, 1.0);
        title.width = 0.47;
        title.borderWidth = 0.20;
        title.setText(gdu::String("Inventory"));
      }

      PlayerInventoryFrame::PlayerInventoryFrame(const PlayerInventoryFrame& frame) : gdgui::GuiComponent(frame)
      {
        inventoryFrames = new InventoryFrame[INVENTORY_FRAMES_AMOUNT];
        components.clear();
        addComponent(&panel);
        title = frame.title;
      }

      PlayerInventoryFrame& PlayerInventoryFrame::operator=(const PlayerInventoryFrame& frame)
      {
        gdgui::GuiComponent::operator=(frame);
        components.clear();
        addComponent(&panel);
        title = frame.title;
        return *this;
      }

      PlayerInventoryFrame::~PlayerInventoryFrame()
      {
        delete[] inventoryFrames;
      }

      const gdm::Vector2 PANEL_OFFSET(0.0, 0.15);
      const float FRAMES_START_SPACE = 0.06;
      const float FRAMES_END_SPACE = 0.02;

      void PlayerInventoryFrame::setInventories(Inventory* inventories)
      {
        components.clear();
        panel = gdgui::Panel();
        panel.setPosition(PANEL_OFFSET);
        panel.setSize(gdm::Vector2(size.x, size.y - PANEL_OFFSET.y - 0.03));
        addComponent(&panel);

        float starty = 0.0;
        for(unsigned int i=0;i<INVENTORY_FRAMES_AMOUNT;i++)
        {
          (inventoryFrames + i)->setWidth(panel.getSize().x - FRAMES_START_SPACE - FRAMES_END_SPACE);
          (inventoryFrames + i)->setPosition(gdm::Vector2(FRAMES_START_SPACE, starty));
          (inventoryFrames + i)->setInventory(inventories + i);

          panel.addComponent((inventoryFrames + i));
          starty+=(inventoryFrames + i)->getSize().y;
        }
      }

      const gdm::Vector2 ICON_POSITION(0.01, 0.02);
      const float ICON_SIZE = 0.05;
      const gdm::Vector2 TITLE_POSITION(0.06, 0.03);

      void PlayerInventoryFrame::render(const gdm::Vector2& referencePosition) const
      {
        gdgui::renderFrame3(referencePosition + position, size, 0.17);
        gdgui::renderTexturedQuad(gdd::INVENTORY_ICON_TEXTURE, referencePosition + position + ICON_POSITION, gdm::Vector2(ICON_SIZE, ICON_SIZE*(gdgui::WINDOW_WIDTH/gdgui::WINDOW_HEIGHT)));
        gdgui::renderText(referencePosition + position + TITLE_POSITION, title);
        gdgui::GuiComponent::render(referencePosition);
      }
    }
  }
}
