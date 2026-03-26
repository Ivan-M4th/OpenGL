#ifndef GD_GUI_GUIDATA_H
#define GD_GUI_GUIDATA_H

#include "../gddef.h"

#include "GuiComponent.h"

#include "../graphics/Shader.h"

#include "../text/TextRenderer.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      extern float WINDOW_WIDTH;
      extern float WINDOW_HEIGHT;

      extern float MOUSE_X;
      extern float MOUSE_Y;
      extern float MOUSE_MOVE_X;
      extern float MOUSE_MOVE_Y;
      extern float MOUSE_SCROLL_X;
      extern float MOUSE_SCROLL_Y;
      extern bool MOUSE_LEFT_BUTTON_PRESSED;
      extern bool MOUSE_RIGHT_BUTTON_PRESSED;

      extern GuiComponent* HOVERED_COMPONENT;
      extern GuiComponent* ACTIVE_COMPONENT;

      extern GuiComponent* HOVERED_SUPPORT_COMPONENT;

      extern gdg::Shader* GUI_SHADER;
      extern gdt::TextRenderer* TEXT_RENDERER;

      void onGuiOpen();
      void onGuiClose();
      void addGuiComponent(GuiComponent*);
      void updateGuiInput();
      void updateGui(float);
      void renderGui();
    }
  }
}

#endif
