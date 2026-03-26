#ifndef GD_GUI_VISIBILITYTABBUTTON_H
#define GD_GUI_VISIBILITYTABBUTTON_H

#include "../gddef.h"

#include "GuiComponent.h"
#include "TabButton.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class VisibilityTabButton : public TabButton
      {
      private:
        unsigned int textureId;
        GuiComponent* component;

      public:
        VisibilityTabButton(GuiComponent*, unsigned int, const gdm::Vector2&, const gdm::Vector2&, TabButton**);
        VisibilityTabButton(const VisibilityTabButton&);
        VisibilityTabButton& operator=(const VisibilityTabButton&);
        virtual ~VisibilityTabButton() override;

        virtual void render(const gdm::Vector2&) const override;
        virtual void onSelect() override;
        virtual void onDeselect() override;
      };
    }
  }
}

#endif
