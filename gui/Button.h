#ifndef GD_GUI_BUTTON_H
#define GD_GUI_BUTTON_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Button : public GuiComponent
      {
      public:
        Button(const gdm::Vector2&, const gdm::Vector2&);
        Button(const Button&);
        Button& operator=(const Button&);
        virtual ~Button() override;

        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
