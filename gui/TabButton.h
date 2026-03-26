#ifndef GD_GUI_TABBUTTON_H
#define GD_GUI_TABBUTTON_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class TabButton : public GuiComponent
      {
      private:
        TabButton** activeTabButton;

      protected:
        bool isSelected() const;

      public:
        TabButton(const gdm::Vector2&, const gdm::Vector2&, TabButton**);
        TabButton(const TabButton&);
        TabButton& operator=(const TabButton&);
        virtual ~TabButton() override;

        virtual void onLeftClick() override;
        virtual void onGuiClose() override;

        virtual void onSelect();
        virtual void onDeselect();
      };
    }
  }
}

#endif
