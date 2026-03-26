#include "KeyPressedEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int KeyPressedEvent::getStaticType()
        {
          return KEY_PRESSED_EVENT;
        }

        KeyPressedEvent::KeyPressedEvent(unsigned int keyCode)
        {
          this->keyCode = keyCode;
        }

        KeyPressedEvent::KeyPressedEvent(const KeyPressedEvent& event)
        {
          keyCode = event.keyCode;
        }

        KeyPressedEvent& KeyPressedEvent::operator=(const KeyPressedEvent& event)
        {
          keyCode = event.keyCode;
          return *this;
        }

        unsigned int KeyPressedEvent::getKeyCode() const
        {
          return keyCode;
        }

        unsigned int KeyPressedEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
