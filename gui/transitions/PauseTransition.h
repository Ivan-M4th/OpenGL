#ifndef GD_GUI_TRANSITIONS_PAUSETRANSITION_H
#define GD_GUI_TRANSITIONS_PAUSETRANSITION_H

#include "../Transition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        class PauseTransition : public Transition
        {
        public:
          PauseTransition(float);
          PauseTransition(const PauseTransition&);
          PauseTransition& operator=(const PauseTransition&);
          virtual ~PauseTransition() override;
        };
      }
    }
  }
}

#endif
