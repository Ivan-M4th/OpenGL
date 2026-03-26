#include "VisibilityTabButton.h"

#include "Gui.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      VisibilityTabButton::VisibilityTabButton(GuiComponent* component, unsigned int textureId, const gdm::Vector2& position, const gdm::Vector2& size, TabButton** activeTabButton) : TabButton(position, size, activeTabButton)
      {
        this->component = component;
        this->textureId = textureId;
      }

      VisibilityTabButton::VisibilityTabButton(const VisibilityTabButton& button) : TabButton(button)
      {
        component = button.component;
        textureId = button.textureId;
      }

      VisibilityTabButton& VisibilityTabButton::operator=(const VisibilityTabButton& button)
      {
        TabButton::operator=(button);
        component = button.component;
        textureId = button.textureId;
        return *this;
      }

      VisibilityTabButton::~VisibilityTabButton()
      {

      }

      void VisibilityTabButton::render(const gdm::Vector2& referencePosition) const
      {
        if(isSelected())
        {
          setColorBlending(0.6, 0.0);
          setBlendColor(0.0, 0.9, 0.8, 1.0);
        }
        else if(HOVERED_COMPONENT == this)
        {
          setColorBlending(0.4, 0.0);
          setBlendColor(0.0, 0.9, 0.8, 1.0);
        }

        renderTexturedQuad(textureId, referencePosition + position, size);
        TabButton::render(referencePosition);

        setColorBlending(0.0, 0.0);
        setBlendColor(1.0, 1.0, 1.0, 0.0);
      }

      void VisibilityTabButton::onSelect()
      {
        TabButton::onSelect();
        component->setVisible(true);
      }

      void VisibilityTabButton::onDeselect()
      {
        TabButton::onDeselect();
        component->setVisible(false);
      }
    }
  }
}
