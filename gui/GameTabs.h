#ifndef GD_GUI_GAMETABS_H
#define GD_GUI_GAMETABS_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../math/Vector2.h"

#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GameTabs : public GuiComponent
      {
      public:
        GameTabs(const gdm::Vector2&, const gdm::Vector2&);
        GameTabs(const GameTabs&);
        GameTabs& operator=(const GameTabs&);
        virtual ~GameTabs() override;

        void setComponents(const ArrayList<GuiComponent*>&);

        virtual void onGuiOpen() override;
        virtual void onGuiClose() override;
      };
    }
  }
}

#endif
