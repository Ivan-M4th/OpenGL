#include "GameTabs.h"

#include "transitions/PauseTransition.h"
#include "transitions/TranslationTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GameTabs::GameTabs(const gdm::Vector2& position, const gdm::Vector2& size) : GuiComponent(position, size)
      {

      }

      GameTabs::GameTabs(const GameTabs& tabs) : GuiComponent(tabs)
      {

      }

      GameTabs& GameTabs::operator=(const GameTabs& tabs)
      {
        GuiComponent::operator=(tabs);
        return *this;
      }

      GameTabs::~GameTabs()
      {

      }

      const float SPACE = 0.05;

      void GameTabs::setComponents(const ArrayList<GuiComponent*>& components)
      {
        float height = 0.0;
        for(unsigned int i=0;i<components.size();i++)
        {
          height+=components[i]->getSize().y;
        }
        height+=((components.size() - 1)*SPACE);

        float y = 0.5*(size.y - height);

        for(unsigned int i=0;i<components.size();i++)
        {
          GuiComponent* component = components[i];
          float x = 0.5*(size.x - component->getSize().x);
          component->setPosition(gdm::Vector2(x, y));
          addComponent(component);
          y+=(component->getSize().y + SPACE);
        }
      }

      const float DELAY = 0.06;

      void GameTabs::onGuiOpen()
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          float x = 0.5*(size.x - components[i]->getSize().x);
          float y = components[i]->getPosition().y;

          components[i]->clearTransitions();
          components[i]->addTransition(new gdguit::PauseTransition(DELAY*i));
          components[i]->addTransition(new gdguit::TranslationTransition(0.3, components[i]->getPosition(), gdm::Vector2(x, y)));
        }
        GuiComponent::onGuiOpen();
      }

      void GameTabs::onGuiClose()
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          float x = -SPACE - components[i]->getSize().x;
          float y = components[i]->getPosition().y;

          components[i]->clearTransitions();
          components[i]->addTransition(new gdguit::PauseTransition(DELAY*i));
          components[i]->addTransition(new gdguit::TranslationTransition(0.3, components[i]->getPosition(), gdm::Vector2(x, y)));
        }
        GuiComponent::onGuiClose();
      }
    }
  }
}
