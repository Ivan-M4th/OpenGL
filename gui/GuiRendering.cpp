#include "GuiRendering.h"

#include <cmath>

#include "Gui.h"

#include "../graphics/Rendering.h"

#include "../data/Assets.h"
#include "../data/ItemAssets.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      const int COLOR_COMPONENT_TYPE = 0;
      const int TEXTURED_COMPONENT_TYPE = 1;
      const int TEXT_COMPONENT_TYPE = 2;

      const float BORDER_WIDTH = 0.01;

      void setRenderingType(int id)
      {
        GUI_SHADER->loadVariable(7, id);
      }

      void useFadeOut(bool x, bool y)
      {

        GUI_SHADER->loadVariable(2, x, y);
      }

      void setFadeOutBounds(float xmin, float xmax, float ymin, float ymax)
      {

        GUI_SHADER->loadVariable(3, xmin, xmax, ymin, ymax);
      }

      void setFadeOutBorderSize(float x, float y)
      {
        GUI_SHADER->loadVariable(4, x, y);
      }

      void setColor(float r, float g, float b, float a)
      {
        GUI_SHADER->loadVariable(8, r, g, b, a);
      }

      void setBlendColor(float r, float g, float b, float a)
      {
        GUI_SHADER->loadVariable(5, r, g, b, a);
      }

      void setColorBlending(float xyz, float a)
      {

        GUI_SHADER->loadVariable(6, xyz, a);
      }

      void getRenderingArea(int* box)
      {
        glGetIntegerv(GL_SCISSOR_BOX, box);
      }

      void setRenderingArea(int* box)
      {
        glScissor(*box, *(box + 1), *(box + 2), *(box + 3));
      }

      void intersectArea(int* box1, int* box2)
      {
        if(*box1 < *box2)
        {
          *box1 = *box2;
        }

        if(*(box1 + 1) < *(box2 + 1))
        {
          *(box1 + 1) = *(box2 + 1);
        }

        if(*(box1 + 2) > *(box2 + 2))
        {
          *(box1 + 2) = *(box2 + 2);
        }

        if(*(box1 + 3) > *(box2 + 3))
        {
          *(box1 + 3) = *(box2 + 3);
        }
      }

      void toScreenArea(const gdm::Vector2& position, const gdm::Vector2& size, int* box)
      {
        float coefx = WINDOW_WIDTH;
        float coefy = WINDOW_HEIGHT;
        *box = (int)(coefx*position.x);
        *(box + 1) = (int)(coefy*position.y);
        *(box + 2) = (int)(coefx*size.x);
        *(box + 3) = (int)(coefy*size.y);
        *(box + 1) = (int)(WINDOW_HEIGHT) - *(box + 1) - *(box + 3);
      }

      gdm::Vector2 toScreenPosition(const gdm::Vector2& position)
      {
        float x = floor(position.x*WINDOW_WIDTH)/WINDOW_WIDTH;
        float y = floor(position.y*WINDOW_HEIGHT)/WINDOW_HEIGHT;
        return gdm::Vector2(x, y);
      }

      void renderFrame(const gdm::Vector2& framePosition, const gdm::Vector2& frameSize)
      {

        setRenderingType(TEXTURED_COMPONENT_TYPE);

        float BORDER_HEIGHT = BORDER_WIDTH*((float)(WINDOW_WIDTH)/(float)(WINDOW_HEIGHT));

        gdm::Vector2 position = toScreenPosition(framePosition);
        gdm::Vector2 size = toScreenPosition(frameSize);

        float frameWidth = size.x - 2.0*BORDER_WIDTH;
        float frameHeight = size.y - 2.0*BORDER_HEIGHT;

        if(frameWidth < 0.0)
        {
          frameWidth = 0.0;
        }

        if(frameHeight < 0.0)
        {
          frameHeight = 0.0;
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_CORE_TEXTURE)->getId());
        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT));
        GUI_SHADER->loadVariable(1, gdm::Vector2(frameWidth, frameHeight));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORE_MESH));

        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_BORDER_TEXTURE)->getId());
        GUI_SHADER->loadVariable(0, position + gdm::Vector2(0.0, BORDER_HEIGHT));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, frameHeight));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_BORDER_L_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT + frameHeight));
        GUI_SHADER->loadVariable(1, gdm::Vector2(frameWidth, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_BORDER_B_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH + frameWidth, BORDER_HEIGHT));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, frameHeight));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_BORDER_R_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH, 0.0));
        GUI_SHADER->loadVariable(1, gdm::Vector2(frameWidth, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_BORDER_T_MESH));

        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_CORNER_TEXTURE)->getId());
        GUI_SHADER->loadVariable(0, position + gdm::Vector2(0.0, 0.0));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORNER_TL_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(0.0, BORDER_HEIGHT + frameHeight));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORNER_BL_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH + frameWidth, BORDER_HEIGHT + frameHeight));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORNER_BR_MESH));

        GUI_SHADER->loadVariable(0, position + gdm::Vector2(BORDER_WIDTH + frameWidth, 0.0));
        GUI_SHADER->loadVariable(1, gdm::Vector2(BORDER_WIDTH, BORDER_HEIGHT));
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORNER_TR_MESH));
      }

      void renderColoredShape(unsigned int textureId, const gdm::Vector2& quadPosition, const gdm::Vector2& quadSize)
      {

        setRenderingType(COLOR_COMPONENT_TYPE);

        gdm::Vector2 position = toScreenPosition(quadPosition);
        gdm::Vector2 size = toScreenPosition(quadSize);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(textureId)->getId());
        GUI_SHADER->loadVariable(0, position);
        GUI_SHADER->loadVariable(1, size);
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORE_MESH));
      }

      void renderColoredQuad(const gdm::Vector2& position, const gdm::Vector2& size)
      {
        renderColoredShape(gdd::QUAD_SHAPE_TEXTURE, position, size);
      }

      void renderFrame2(const gdm::Vector2& position, const gdm::Vector2& size)
      {
        setColor(0.097, 0.207, 0.25, 0.8);
        renderColoredQuad(position, size);
      }

      const float FRAME3_BORDER_SIZE = 0.025;

      void renderFrame3(const gdm::Vector2& position, const gdm::Vector2& size, float labelWidth)
      {

        setRenderingType(COLOR_COMPONENT_TYPE);

        gdm::Vector2 borderSize(FRAME3_BORDER_SIZE, FRAME3_BORDER_SIZE*(WINDOW_WIDTH/WINDOW_HEIGHT));

        labelWidth-=2.0*borderSize.x;
        if(labelWidth < 0.0)
        {
          labelWidth = 0.0;
        }
        gdm::Vector2 labelSize(labelWidth, borderSize.y);

        float coreSize = size.y - labelSize.y;
        if(coreSize < 0.0)
        {
          coreSize = 0.0;
        }

        setColor(0.097, 0.207, 0.25, 0.8);
        renderColoredShape(gdd::ROUNDED_SHAPE_TEXTURE, position, borderSize);
        renderColoredQuad(position + gdm::Vector2(borderSize.x, 0.0), labelSize);
        renderColoredShape(gdd::TRIANGLE_SHAPE_TEXTURE, position + gdm::Vector2(borderSize.x + labelSize.x, 0.0), borderSize);
        renderColoredQuad(position + gdm::Vector2(0.0, labelSize.y), gdm::Vector2(size.x, coreSize));
      }

      void renderTexturedQuad(unsigned int textureId, const gdm::Vector2& quadPosition, const gdm::Vector2& quadSize)
      {
        gdm::Vector2 position = toScreenPosition(quadPosition);
        gdm::Vector2 size = toScreenPosition(quadSize);

        setRenderingType(TEXTURED_COMPONENT_TYPE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(textureId)->getId());
        GUI_SHADER->loadVariable(0, position);
        GUI_SHADER->loadVariable(1, size);
        gdg::render2DIMesh(gdd::getMesh(gdd::FRAME_CORE_MESH));
      }

      void renderHoveredBox(const gdm::Vector2& position, const gdm::Vector2& size)
      {
        renderTexturedQuad(gdd::GUI_HOVERED_TEXTURE, position, size);
      }

      void renderItemIcon(unsigned int itemId, const gdm::Vector2& iconPosition, const gdm::Vector2& iconSize)
      {
        gdm::Vector2 position = toScreenPosition(iconPosition);
        gdm::Vector2 size = toScreenPosition(iconSize);


        setRenderingType(TEXTURED_COMPONENT_TYPE);

        glActiveTexture(GL_TEXTURE0);

        gdd::ItemAsset* itemAsset = gdd::getItemAsset(itemId);
        int meshId = itemAsset->iconMeshId;
        int textureId = itemAsset->iconTexture;

        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(textureId)->getId());
        GUI_SHADER->loadVariable(0, position);
        GUI_SHADER->loadVariable(1, size);
        gdg::render2DIMesh(gdd::getItemIconMesh(meshId));
      }

      void renderText(const gdm::Vector2& position, const gdt::Text& text)
      {
        GUI_SHADER->bind();
        setRenderingType(TEXT_COMPONENT_TYPE);

        GUI_SHADER->loadVariable(0, position + text.position);
        GUI_SHADER->loadVariable(1, gdm::Vector2(1.0, WINDOW_WIDTH/WINDOW_HEIGHT));
        setColor(text.color.getX(), text.color.getY(), text.color.getZ(), 1.0);
        GUI_SHADER->loadVariable(9, text.width);
        GUI_SHADER->loadVariable(10, text.borderWidth);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::DEFAULT_FONT_ATLAS_TEXTURE)->getId());
        gdg::render2DIMesh(text.getMesh());
      }
    }
  }
}
