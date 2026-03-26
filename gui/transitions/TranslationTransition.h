#ifndef GD_GUI_TRANSITIONS_TRANSLATIONTRANSITION_H
#define GD_GUI_TRANSITIONS_TRANSLATIONTRANSITION_H

#include "../../gddef.h"

#include "../Transition.h"

#include "../../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        class TranslationTransition : public Transition
        {
        protected:
          gdm::Vector2 start;
          gdm::Vector2 end;

        public:
          TranslationTransition(float, const gdm::Vector2&, const gdm::Vector2&);
          TranslationTransition(const TranslationTransition&);
          TranslationTransition& operator=(const TranslationTransition&);
          virtual ~TranslationTransition() override;

          virtual gdm::Vector2 getPosition(const gdm::Vector2&) const override;
        };
      }
    }
  }
}

#endif
