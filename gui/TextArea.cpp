#include "TextArea.h"

#include "../text/Fonts.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      TextArea::TextArea() : GuiComponent(gdm::Vector2(), gdm::Vector2())
      {

      }

      TextArea::TextArea(const gdm::Vector2& position, const gdm::Vector2& size, const gdt::Font* font, float textSize, bool centered) : GuiComponent(position, size), text(font, textSize, size.x, centered)
      {

      }

      TextArea::TextArea(const TextArea& area) : GuiComponent(area), text(area.text)
      {

      }

      TextArea& TextArea::operator=(const TextArea& area)
      {
        GuiComponent::operator=(area);
        text = area.text;
        return *this;
      }

      TextArea::~TextArea()
      {

      }

      void TextArea::setText(const gdu::String& string)
      {
        text.setText(string);
      }

      void TextArea::setTextColor(const gdm::Vector3& color)
      {
        text.color = color;
      }

      void TextArea::setTextCentered(bool centered)
      {
        text.centered = centered;
      }

      void TextArea::setSize(const gdm::Vector2& size)
      {
        GuiComponent::setSize(size);
        text.maxLineSize = size.x;
        text.updateMesh();
      }

      void TextArea::setTextSize(float textSize)
      {
        text.size = textSize;
      }

      void TextArea::render(const gdm::Vector2& referencePosition) const
      {
        setColor(0.0, 0.0, 0.0, 0.5);
        renderColoredQuad(referencePosition + position + gdm::Vector2(0.005, 0.007), size);
        setColor(0.1835, 0.281, 0.32, 1.0);
        renderColoredQuad(referencePosition + position, size);
        renderText(referencePosition + position, text);
        GuiComponent::render(referencePosition);
      }
    }
  }
}
