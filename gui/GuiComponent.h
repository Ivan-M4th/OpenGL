#ifndef GD_GUI_GUICOMPONENT_H
#define GD_GUI_GUICOMPONENT_H

#include "../gddef.h"

#include "Transition.h"

#include "../math/Vector2.h"

#include "../utils/ArrayList.h"
#include "../utils/Pointer.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GuiComponent
      {
        friend class Panel;

      protected:
        gdm::Vector2 position;
        gdm::Vector2 size;

        gdm::Vector2 childrenOffset;
        ArrayList<GuiComponent*> components;
        ArrayList<Transition*> transitions;
        bool visible;
        bool hoverable;
        bool support;
        bool dragable;

        bool isInside(const gdm::Vector2&, float, float) const;
        void renderChildren(const gdm::Vector2&) const;
      public:
        GuiComponent(const gdm::Vector2&, const gdm::Vector2&);
        GuiComponent(const GuiComponent&);
        GuiComponent& operator=(const GuiComponent&);
        virtual ~GuiComponent();

        bool isVisible() const;
        bool isDragable() const;
        const gdm::Vector2& getPosition() const;
        const gdm::Vector2& getSize() const;

        void updateMouse(const gdm::Vector2&);
        void clearTransitions();
        void addTransition(Transition*);

        virtual void setVisible(bool);
        virtual void addComponent(GuiComponent*);
        virtual void setPosition(const gdm::Vector2&);
        virtual void setSize(const gdm::Vector2&);

        virtual void onHovered();
        virtual void onActive();
        virtual void onLeftClick();
        virtual void onGuiOpen();
        virtual void onGuiClose();
        virtual void onMouseInside();
        virtual void update(float);

        virtual void render(const gdm::Vector2&) const;

      };
    }
  }
}

#endif
