#include "InventoryDisplayBelt.h"

#include <cmath>

#include "../gui/Gui.h"
#include "../gui/GuiRendering.h"
#include "../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      InventoryDisplayBelt::InventoryDisplayBelt(const gdm::Vector2& position, const gdm::Vector2& size) : gdgui::GuiComponent(position, size)
      {
        index = 0;
        inventory = NULL;
        nextIndex = 0;
        beltPosition = 0.0;
        speed = 0.0;
      }

      InventoryDisplayBelt::InventoryDisplayBelt(const InventoryDisplayBelt& belt) : gdgui::GuiComponent(belt)
      {
        index = belt.index;
        inventory = belt.inventory;
        nextIndex = belt.nextIndex;
        beltPosition = belt.beltPosition;
        speed = belt.speed;
      }

      InventoryDisplayBelt& InventoryDisplayBelt::operator=(const InventoryDisplayBelt& belt)
      {
        gdgui::GuiComponent::operator=(belt);
        index = belt.index;
        inventory = belt.inventory;
        nextIndex = belt.nextIndex;
        beltPosition = belt.beltPosition;
        speed = belt.speed;
        return *this;
      }

      InventoryDisplayBelt::~InventoryDisplayBelt()
      {

      }

      const float SPACE = 0.015;

      gdm::Vector2 InventoryDisplayBelt::getCenter() const
      {
        if(displays.size() == 0)
        {
          return gdm::Vector2(0.5*size.x, 0.5*size.y);
        }
        float x = 0.5*(size.x - displays[0].getSize().x) - beltPosition*(displays[0].getSize().x + SPACE);
        float y = 0.5*(size.y - displays[0].getSize().y);
        return gdm::Vector2(x, y);
      }

      int InventoryDisplayBelt::getDifference(unsigned int i) const
      {
        int size = inventory->getSize();

        int difference = (int)(i) - (int)(index);
        if(abs(difference) > size/2)
        {
          if(difference >= 0)
          {
            difference-=size;
          }
          else
          {
            difference+=size;
          }
        }
        return difference;
      }

      void InventoryDisplayBelt::updateDisplay(unsigned int i, const gdm::Vector2& center)
      {
        int difference = getDifference(i);
        float x = difference*(SPACE + displays[i].getSize().x);
        float y = 0.0;
        displays[i].setPosition(center + gdm::Vector2(x, y));
      }

      void InventoryDisplayBelt::updateDisplays()
      {
        for(unsigned int i=0;i<displays.size();i++)
        {
          updateDisplay(i, getCenter());
        }
      }

      void InventoryDisplayBelt::buildDisplays()
      {
        displays.setSize(inventory->getSize());
        for(unsigned int i=0;i<displays.size();i++)
        {
          updateDisplay(i, getCenter());
          displays[i].setItem(inventory, i);
          addComponent(&displays[i]);
        }
      }

      void InventoryDisplayBelt::setInventory(Inventory* inventory)
      {
        assert(inventory != NULL);
        assert(inventory->getSize() > 0);
        index = 0;
        nextIndex = 0;
        beltPosition = 0.0;
        speed = 0.0;
        this->inventory = inventory;
        buildDisplays();
      }

      const float CHANGE_DISPLAY_TIME = 0.2;

      void InventoryDisplayBelt::next()
      {
        nextIndex++;
        if(nextIndex >= displays.size())
        {
          nextIndex = 0;
        }

        speed = (float)getDifference(nextIndex)/CHANGE_DISPLAY_TIME;
      }

      void InventoryDisplayBelt::previous()
      {
        if(nextIndex == 0)
        {
          nextIndex = displays.size() - 1;
        }
        else
        {
          nextIndex--;
        }

        speed = (float)getDifference(nextIndex)/CHANGE_DISPLAY_TIME;
      }

      unsigned int InventoryDisplayBelt::getSelectedSlot() const
      {
        return nextIndex;
      }

      const float DEFAULT_SPEED = 1.0/CHANGE_DISPLAY_TIME;

      void InventoryDisplayBelt::update(float timePassed)
      {
        if(inventory == NULL)
        {
          return;
        }

        beltPosition+=(speed*timePassed);
        if(speed > 0.0)
        {
          while(beltPosition >= 1.0)
          {
            index++;
            if(index >= displays.size())
            {
              index = 0;
            }
            beltPosition-=1.0;

            if(index == nextIndex)
            {
              beltPosition = 0.0;
              speed = 0.0;
            }
          }
        }
        else if(speed < 0.0)
        {
          while(beltPosition <= -1.0)
          {
            if(index == 0)
            {
              index = displays.size() - 1;
            }
            else
            {
              index--;
            }
            beltPosition+=1.0;

            if(index == nextIndex)
            {
              beltPosition = 0.0;
              speed = 0.0;
            }
          }
        }

        if(index == nextIndex)
        {
          if(beltPosition > 0.0)
          {
            beltPosition-=(DEFAULT_SPEED*timePassed);

            if(beltPosition < 0.0)
            {
              beltPosition = 0.0;
            }
          }
          else if(beltPosition < 0.0)
          {
            beltPosition+=(DEFAULT_SPEED*timePassed);

            if(beltPosition > 0.0)
            {
              beltPosition = 0.0;
            }
          }
        }


        updateDisplays();
        gdgui::GuiComponent::update(timePassed);
      }



      void InventoryDisplayBelt::render(const gdm::Vector2& referencePosition) const
      {
        gdgui::useFadeOut(true, false);
        gdgui::setFadeOutBounds(referencePosition.x + position.x, referencePosition.x + position.x + size.x, 0.0, 1.0);
        gdgui::setFadeOutBorderSize(0.1, 0.1);
        renderChildren(referencePosition);

        float sizex = 0.062;
        float sizey = 0.110;
        float x = 0.5*(size.x - sizex);
        float y = 0.5*(size.y - sizey);
        gdgui::renderTexturedQuad(gdd::ITEM_SELECTOR_TEXTURE, referencePosition + position + gdm::Vector2(x, y), gdm::Vector2(sizex, sizey));

        gdgui::useFadeOut(false, false);
      }
    }
  }
}
