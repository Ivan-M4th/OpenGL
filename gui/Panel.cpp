#include "Panel.h"

#include "Gui.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Panel::Panel() : GuiComponent(gdm::Vector2(), gdm::Vector2())
      {
        minOffsetY = 0.0;
        support = true;
      }

      Panel::Panel(const gdm::Vector2& position, const gdm::Vector2& size) : GuiComponent(position, size)
      {
        minOffsetY = 0.0;
        support = true;
      }

      Panel::Panel(const Panel& panel) : GuiComponent(panel)
      {
        minOffsetY = panel.minOffsetY;
      }

      Panel& Panel::operator=(const Panel& panel)
      {
        GuiComponent::operator=(panel);
        minOffsetY = panel.minOffsetY;
        return *this;
      }

      Panel::~Panel()
      {

      }

      void Panel::checkOffset()
      {
        if(childrenOffset.y > 0.0)
        {
          childrenOffset.y = 0.0;
        }
        else if(childrenOffset.y < minOffsetY)
        {
          childrenOffset.y = minOffsetY;
        }
      }

      void Panel::addComponent(GuiComponent* component)
      {
        GuiComponent::addComponent(component);
        float newMinOffsetY = size.y - component->position.y - component->size.y;
        if(newMinOffsetY < minOffsetY)
        {
          minOffsetY = newMinOffsetY;
        }
      }

      void Panel::onHovered()
      {
        GuiComponent::onActive();
        childrenOffset = childrenOffset + gdm::Vector2(0.0, MOUSE_SCROLL_Y);
        checkOffset();
      }
    }
  }
}
