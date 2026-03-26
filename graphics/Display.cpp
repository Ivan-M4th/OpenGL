#include "Display.h"

#include "../gddef.h"

#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>

#include "../events/Events.h"
#include "../events/types/LeftClickEvent.h"
#include "../events/types/MouseScrollEvent.h"
#include "../events/types/MouseGrabEvent.h"

#include "../gui/Gui.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {

      SDL_Window* DISPLAY_WINDOW;
      SDL_GLContext GL_CONTEXT;
      ArrayList<SDL_Keycode> keysPressed;
      ArrayList<SDL_Keycode> toggledKeys;

      ArrayList<unsigned int> toggledMouseButtons;

      bool DISPLAY_WINDOW_CLOSED = false;
      int MOUSE_MOVE_X = 0;
      int MOUSE_MOVE_Y = 0;
      int MOUSE_X = 0;
      int MOUSE_Y = 0;
      int MOUSE_WHEEL_X = 0;
      int MOUSE_WHEEL_Y = 0;
      int MOUSE_SCROLL_X = 0;
      int MOUSE_SCROLL_Y = 0;

      void initDisplay(const char* title, int width, int height)
      {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        DISPLAY_WINDOW = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        GL_CONTEXT = SDL_GL_CreateContext(DISPLAY_WINDOW);
        DISPLAY_WINDOW_CLOSED = false;
        GLenum status = glewInit();
        if(status != GLEW_OK)
        {
          std::cerr << "ERROR: GLEW could not be initialized!" << std::endl;
          exit(EXIT_FAILURE);
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
      }

      void cleanDisplay()
      {
        SDL_GL_DeleteContext(GL_CONTEXT);
        SDL_DestroyWindow(DISPLAY_WINDOW);
        SDL_Quit();
      }

      void updateDisplay()
      {
        //swap buffers
        SDL_GL_SwapWindow(DISPLAY_WINDOW);

        //les evenements
        MOUSE_MOVE_X = 0;
        MOUSE_MOVE_Y = 0;
        MOUSE_WHEEL_X = 0;
        MOUSE_WHEEL_Y = 0;
        MOUSE_SCROLL_X = 0;
        MOUSE_SCROLL_Y = 0;
        toggledKeys.clear();
        toggledMouseButtons.clear();

        SDL_GetMouseState(&MOUSE_X, &MOUSE_Y);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
          if(event.type == SDL_QUIT)
          {
            DISPLAY_WINDOW_CLOSED = true;
          }
          else
          {
            handleKeys(event);
          }
        }
      }

      bool mouseGrabed()
      {
        return SDL_GetRelativeMouseMode();
      }

      void grabMouse()
      {
        SDL_SetRelativeMouseMode((SDL_bool)(!SDL_GetRelativeMouseMode()));
        gdet::MouseGrabEvent event(mouseGrabed());
        gde::onEvent(event);

        if(mouseGrabed())
        {
          gdgui::onGuiClose();
        }
        else
        {
          gdgui::onGuiOpen();
        }
      }

      void handleKeys(const SDL_Event& event)
      {
        if(event.type == SDL_KEYDOWN)
        {
          SDL_Keycode key = event.key.keysym.sym;
          if(!isPressed(key))
          {
            toggledKeys.add(key);
          }
          onKeyPressed(key);
        }
        else if(event.type == SDL_KEYUP)
        {
          SDL_Keycode key = event.key.keysym.sym;
          onKeyReleased(key);
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
          toggledMouseButtons.add(event.button.button);
          gdet::LeftClickEvent e;
          gde::onEvent(e);
        }
        else if(mouseGrabed() && event.type == SDL_MOUSEMOTION)
        {
          MOUSE_MOVE_X = event.motion.xrel;
          MOUSE_MOVE_Y = event.motion.yrel;
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
          MOUSE_SCROLL_X = event.wheel.x;
          MOUSE_SCROLL_Y = event.wheel.y;
          gdet::MouseScrollEvent e(MOUSE_SCROLL_X, MOUSE_SCROLL_Y);
          gde::onEvent(e);
        }
      }

      bool isToggledMouseButton(unsigned int button)
      {
        return toggledMouseButtons.contains(button);
      }

      void onKeyPressed(const SDL_Keycode& key)
      {
        if(!keysPressed.contains(key))
        {
          keysPressed.add(key);
        }
      }

      bool isToggledKey(const SDL_Keycode& key)
      {
        return toggledKeys.contains(key);
      }

      void onKeyReleased(const SDL_Keycode& key)
      {
        keysPressed.removeElement(key);
      }

      bool isPressed(const SDL_Keycode& key)
      {
        return keysPressed.contains(key);
      }

      void clearDisplay(float r, float g, float b, float a)
      {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
      }
    }
  }
}
