#include "TranslationTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        TranslationTransition::TranslationTransition(float duration, const gdm::Vector2& start, const gdm::Vector2& end) : Transition(duration)
        {
          this->start = start;
          this->end = end;
        }

        TranslationTransition::TranslationTransition(const TranslationTransition& transition) : Transition(transition)
        {
          start = transition.start;
          end = transition.end;
        }

        TranslationTransition& TranslationTransition::operator=(const TranslationTransition& transition)
        {
          Transition::operator=(transition);
          start = transition.start;
          end = transition.end;
          return *this;
        }

        TranslationTransition::~TranslationTransition()
        {

        }

        gdm::Vector2 TranslationTransition::getPosition(const gdm::Vector2& position) const
        {
          if(isFinished())
          {
            return end;
          }
          else
          {
            float t = time/duration;

            return start + t*(end - start);
          }
        }
      }
    }
  }
}
