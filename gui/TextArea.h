#ifndef GD_GUI_TEXTAREA_H
#define GD_GUI_TEXTAREA_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"
#include "../math/Vector3.h"

#include "../text/Font.h"
#include "../text/Text.h"

#include "../utils/String.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class TextArea : public GuiComponent
      {
      protected:
        gdt::Text text;

      public:
        TextArea();
        TextArea(const gdm::Vector2&, const gdm::Vector2&, const gdt::Font*, float, bool);
        TextArea(const TextArea&);
        TextArea& operator=(const TextArea&);
        virtual ~TextArea() override;

        void setText(const gdu::String&);
        void setTextColor(const gdm::Vector3&);
        void setTextCentered(bool);
        void setTextSize(float);

        virtual void setSize(const gdm::Vector2&) override;
        virtual void render(const gdm::Vector2&) const override;
      };
    }
  }
}

#endif
