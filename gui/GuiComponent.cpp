#include "GuiComponent.h"

#include "Gui.h"
#include "GuiRendering.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GuiComponent::GuiComponent(const gdm::Vector2& position, const gdm::Vector2& size)
      {
        this->position = position;
        this->size = size;
        visible = true;
        hoverable = true;
        support = false;
        dragable = false;
      }

      GuiComponent::GuiComponent(const GuiComponent& component)
      {
        position = component.position;
        size = component.size;
        components = component.components;
        childrenOffset = component.childrenOffset;
        visible = component.visible;
        hoverable = component.hoverable;
        support = component.support;
        dragable = component.dragable;
      }

      GuiComponent& GuiComponent::operator=(const GuiComponent& component)
      {
        position = component.position;
        size = component.size;
        components = component.components;
        childrenOffset = component.childrenOffset;
        visible = component.visible;
        hoverable = component.hoverable;
        support = component.support;
        dragable = component.dragable;
        return *this;
      }

      GuiComponent::~GuiComponent()
      {
        for(unsigned int i=0;i<transitions.size();i++)
        {
          delete transitions[i];
        }
      }

      bool GuiComponent::isInside(const gdm::Vector2& referencePosition, float x, float y) const
      {
        float px = position.x + referencePosition.x;
        float py = position.y + referencePosition.y;
        if(px <= x && x <= px + size.x)
        {
          if(py <= y && y <= py + size.y)
          {
            return true;
          }
        }
        return false;
      }

      void GuiComponent::renderChildren(const gdm::Vector2& referencePosition) const
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          if(components[i]->visible)
          {
            components[i]->render(referencePosition + position + childrenOffset);
          }
        }
      }

      bool GuiComponent::isVisible() const
      {
        return visible;
      }

      bool GuiComponent::isDragable() const
      {
        return dragable;
      }

      const gdm::Vector2& GuiComponent::getPosition() const
      {
        return position;
      }

      const gdm::Vector2& GuiComponent::getSize() const
      {
        return size;
      }

      void GuiComponent::setPosition(const gdm::Vector2& position)
      {
        this->position = position;
      }

      void GuiComponent::setSize(const gdm::Vector2& size)
      {
        this->size = size;
      }

      void GuiComponent::setVisible(bool visible)
      {
        this->visible = visible;
      }

      void GuiComponent::addComponent(GuiComponent* component)
      {
        components.add(component);
      }

      void GuiComponent::clearTransitions()
      {
        for(unsigned int i=0;i<transitions.size();i++)
        {
          delete transitions[i];
        }
        transitions.clear();
      }

      void GuiComponent::addTransition(Transition* transition)
      {
        transitions.add(transition);
      }

      void GuiComponent::updateMouse(const gdm::Vector2& referencePosition)
      {
        if(isInside(referencePosition, MOUSE_X, MOUSE_Y))
        {
          onMouseInside();
          for(unsigned int i=0;i<components.size();i++)
          {
            if(components[i]->visible)
            {
              components[i]->updateMouse(referencePosition + position + childrenOffset);
            }
          }
        }
      }

      void GuiComponent::render(const gdm::Vector2& referencePosition) const
      {
        int box[4];
        getRenderingArea(box);

        int newBox[4];
        toScreenArea(referencePosition + position, size, newBox);
        intersectArea(newBox, box);
        setRenderingArea(newBox);
        renderChildren(referencePosition);

        setRenderingArea(box);
      }

      void GuiComponent::onMouseInside()
      {
        if(hoverable)
        {
          HOVERED_COMPONENT = this;
          if(support)
          {
            HOVERED_SUPPORT_COMPONENT = this;
          }
        }
      }

      void GuiComponent::update(float timePassed)
      {
        if(transitions.size() > 0)
        {
          transitions[0]->update(timePassed);
          setPosition(transitions[0]->getPosition(position));

          if(transitions[0]->isFinished())
          {
            delete transitions[0];
            transitions.remove(0);
          }
        }

        for(unsigned int i=0;i<components.size();i++)
        {
          if(components[i]->visible)
          {
            components[i]->update(timePassed);
          }
        }
      }

      void GuiComponent::onHovered()
      {

      }

      void GuiComponent::onActive()
      {

      }

      void GuiComponent::onLeftClick()
      {

      }

      void GuiComponent::onGuiOpen()
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          components[i]->onGuiOpen();
        }
      }

      void GuiComponent::onGuiClose()
      {
        for(unsigned int i=0;i<components.size();i++)
        {
          components[i]->onGuiClose();
        }
      }
    }
  }
}
