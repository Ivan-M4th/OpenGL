#include "Frame.h"

#include "GuiRendering.h"
#include "Gui.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Frame::Frame(const gdm::Vector2& position, const gdm::Vector2& size) : GuiComponent(position, size)
      {

      }

      Frame::Frame(const Frame& frame) : GuiComponent(frame)
      {

      }

      Frame& Frame::operator=(const Frame& frame)
      {
        GuiComponent::operator=(frame);
        return *this;
      }

      Frame::~Frame()
      {

      }


      void Frame::render(const gdm::Vector2& referencePosition) const
      {
        renderFrame2(referencePosition + position, size);
        GuiComponent::render(referencePosition);
      }
    }
  }
}
