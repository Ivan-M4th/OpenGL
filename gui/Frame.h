#ifndef GD_GUI_FRAME_H
#define GD_GUI_FRAME_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Frame : public GuiComponent
      {
      public:
        Frame(const gdm::Vector2&, const gdm::Vector2&);
        Frame(const Frame&);
        Frame& operator=(const Frame&);
        virtual ~Frame() override;

        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
