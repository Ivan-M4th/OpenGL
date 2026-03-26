#ifndef GD_TEXT_TEXT_H
#define GD_TEXT_TEXT_H

#include "../gddef.h"

#include "Font.h"

#include "../utils/String.h"
#include "../utils/Pointer.h"

#include "../graphics/Mesh.h"

#include "../math/Vector2.h"
#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class Text
      {
      private:
        gdu::String string;
        gdg::Mesh mesh;

        void buildMesh();
      public:
        const Font* font;
        float size;
        float maxLineSize;
        bool centered;
        gdm::Vector2 position;
        gdm::Vector3 color;
        float width = 0.45;
        float borderWidth = 0.32;

        Text();
        Text(const Font*, float, float, bool);
        Text(const Text&);
        Text& operator=(const Text&);

        void setText(const gdu::String&);
        const gdg::Mesh* getMesh() const;
        void updateMesh();
      };
    }
  }
}

#endif
