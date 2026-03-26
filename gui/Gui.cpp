#include "Gui.h"

#include "GuiRendering.h"

#include "../utils/ArrayList.h"

#include "../events/Events.h"
#include "../events/types/GuiToggleEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      float WINDOW_WIDTH = 0.0;
      float WINDOW_HEIGHT = 0.0;

      float MOUSE_X = 0.0;
      float MOUSE_Y = 0.0;
      float MOUSE_MOVE_X = 0.0;
      float MOUSE_MOVE_Y = 0.0;
      float MOUSE_SCROLL_X = 0.0;
      float MOUSE_SCROLL_Y = 0.0;
      bool MOUSE_LEFT_BUTTON_PRESSED = false;
      bool MOUSE_RIGHT_BUTTON_PRESSED = false;

      GuiComponent* HOVERED_COMPONENT = NULL;
      GuiComponent* ACTIVE_COMPONENT = NULL;

      GuiComponent* HOVERED_SUPPORT_COMPONENT = NULL;

      gdg::Shader* GUI_SHADER = NULL;
      gdt::TextRenderer* TEXT_RENDERER = NULL;

      ArrayList<GuiComponent*> components;

      void onGuiOpen()
      {
        gdet::GuiToggleEvent event(true);
        gde::onEvent(event);

        for(unsigned int i=0;i<components.size();i++)
        {
          components[i]->onGuiOpen();
        }
      }

      void onGuiClose()
      {
        HOVERED_COMPONENT = NULL;
        ACTIVE_COMPONENT = NULL;
        HOVERED_SUPPORT_COMPONENT = NULL;

        gdet::GuiToggleEvent event(true);
        gde::onEvent(event);

        for(unsigned int i=0;i<components.size();i++)
        {
          components[i]->onGuiClose();
        }
      }

      void addGuiComponent(GuiComponent* component)
      {
        components.add(component);
      }

      void onLeftClick()
      {
        ACTIVE_COMPONENT = HOVERED_COMPONENT;
        if(ACTIVE_COMPONENT != NULL)
        {
          ACTIVE_COMPONENT->onLeftClick();
        }
      }

      void updateGuiInput()
      {
        HOVERED_COMPONENT = NULL;
        HOVERED_SUPPORT_COMPONENT = NULL;

        for(unsigned int i=0;i<components.size();i++)
        {
          if(components[i]->isVisible())
          {
            components[i]->updateMouse(gdm::Vector2());
          }
        }

        if(HOVERED_COMPONENT != NULL)
        {
          HOVERED_COMPONENT->onHovered();
        }

        if(HOVERED_SUPPORT_COMPONENT != NULL)
        {
          HOVERED_SUPPORT_COMPONENT->onHovered();
        }

        if(ACTIVE_COMPONENT != NULL)
        {
          if(!ACTIVE_COMPONENT->isVisible())
          {
            ACTIVE_COMPONENT = NULL;
          }
        }

        if(MOUSE_LEFT_BUTTON_PRESSED)
        {
          onLeftClick();
        }

        if(ACTIVE_COMPONENT != NULL)
        {
          ACTIVE_COMPONENT->onActive();
        }
      }

      void updateGui(float timePassed)
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          if(components[i]->isVisible())
          {
            components[i]->update(timePassed);
          }
        }
      }

      void renderGui()
      {
        GUI_SHADER->bind();
        useFadeOut(false, false);
        setFadeOutBounds(0.0, 1.0, 0.0, 1.0);
        for(unsigned int i=0;i<components.size();i++)
        {
          if(components[i]->isVisible())
          {
            components[i]->render(gdm::Vector2());
          }
        }
      }
    }
  }
}
