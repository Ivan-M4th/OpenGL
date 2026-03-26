#ifndef GD_GUI_PANEL_H
#define GD_GUI_PANEL_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Panel : public GuiComponent
      {
      protected:
        float minOffsetY;

        void checkOffset();
      public:
        Panel();
        Panel(const gdm::Vector2&, const gdm::Vector2&);
        Panel(const Panel&);
        Panel& operator=(const Panel&);
        virtual ~Panel() override;

        virtual void addComponent(GuiComponent*) override;
        virtual void onHovered() override;
      };
    }
  }
}

#endif
