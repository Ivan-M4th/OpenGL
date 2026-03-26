#include "Button.h"

#include <iostream>

#include "Gui.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Button::Button(const gdm::Vector2& position, const gdm::Vector2& size) : GuiComponent(position, size)
      {

      }

      Button::Button(const Button& button) : GuiComponent(button)
      {

      }

      Button& Button::operator=(const Button& button)
      {
        GuiComponent::operator=(button);
        return *this;
      }

      Button::~Button()
      {

      }

      void Button::render(const gdm::Vector2& referencePosition) const
      {
        setColor(0.1835, 0.281, 0.32, 0.8);
        renderColoredQuad(referencePosition + position, size);
        if(HOVERED_COMPONENT == this)
        {
          renderHoveredBox(referencePosition + position, size);
        }

        if(MOUSE_LEFT_BUTTON_PRESSED)
        {
          std::cout << "left click" << std::endl;
        }
        else if(MOUSE_RIGHT_BUTTON_PRESSED)
        {
          std::cout << "right click" << std::endl;
        }
        GuiComponent::render(referencePosition);
      }
    }
  }
}
