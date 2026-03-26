#include "PauseTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        PauseTransition::PauseTransition(float duration) : Transition(duration)
        {

        }

        PauseTransition::PauseTransition(const PauseTransition& transition) : Transition(transition)
        {

        }

        PauseTransition& PauseTransition::operator=(const PauseTransition& transition)
        {
          Transition::operator=(transition);
          return *this;
        }

        PauseTransition::~PauseTransition()
        {

        }
      }
    }
  }
}
