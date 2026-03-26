#include "TabButton.h"

#include "Gui.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      TabButton::TabButton(const gdm::Vector2& position, const gdm::Vector2& size, TabButton** activeTabButton) : GuiComponent(position, size)
      {
        this->activeTabButton = activeTabButton;
      }

      TabButton::TabButton(const TabButton& button) : GuiComponent(button)
      {
        activeTabButton = button.activeTabButton;
      }

      TabButton& TabButton::operator=(const TabButton& button)
      {
        GuiComponent::operator=(button);
        activeTabButton = button.activeTabButton;
        return *this;
      }

      TabButton::~TabButton()
      {

      }

      bool TabButton::isSelected() const
      {
        return *activeTabButton == this;
      }

      void TabButton::onLeftClick()
      {
        GuiComponent::onLeftClick();
        if(*activeTabButton != NULL)
        {
          (*activeTabButton)->onDeselect();
        }

        if(*activeTabButton == this)
        {
          *activeTabButton = NULL;
        }
        else
        {
          *activeTabButton = this;
          onSelect();
        }
      }

      void TabButton::onGuiClose()
      {
        if(*activeTabButton != NULL)
        {
          (*activeTabButton)->onDeselect();
          *activeTabButton = NULL;
        }
      }

      void TabButton::onSelect()
      {

      }

      void TabButton::onDeselect()
      {

      }
    }
  }
}
