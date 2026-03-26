#ifndef GD_GUI_GUIRENDERING_H
#define GD_GUI_GUIRENDERING_H

#include "../gddef.h"

#include "../math/Vector2.h"

#include "../text/Text.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      void useFadeOut(bool, bool);
      void setFadeOutBounds(float, float, float, float);
      void setFadeOutBorderSize(float, float);
      void setColor(float, float, float, float);
      void setBlendColor(float, float, float, float);
      void setColorBlending(float, float);
      void setRenderingType(int);

      void getRenderingArea(int*);
      void intersectArea(int*, int*);
      void toScreenArea(const gdm::Vector2&, const gdm::Vector2&, int*);
      void setRenderingArea(unsigned int, unsigned int, unsigned int, unsigned int);
      void setRenderingArea(int*);

      void renderFrame1(const gdm::Vector2&, const gdm::Vector2&);
      void renderColoredShape(unsigned int, const gdm::Vector2&, const gdm::Vector2&);
      void renderColoredQuad(const gdm::Vector2&, const gdm::Vector2&);
      void renderFrame2(const gdm::Vector2&, const gdm::Vector2&);
      void renderFrame3(const gdm::Vector2&, const gdm::Vector2&, float);
      void renderTexturedQuad(unsigned int, const gdm::Vector2&, const gdm::Vector2&);
      void renderHoveredBox(const gdm::Vector2&, const gdm::Vector2&);
      void renderItemIcon(unsigned int, const gdm::Vector2&, const gdm::Vector2&);
      void renderText(const gdm::Vector2&, const gdt::Text&);
    }
  }
}

#endif
