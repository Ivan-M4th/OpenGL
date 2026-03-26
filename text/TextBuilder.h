#ifndef GD_TEXT_TEXTBUILDER_H
#define GD_TEXT_TEXTBUILDER_H

#include "../gddef.h"

#include "Font.h"
#include "Line.h"

#include "../utils/String.h"

#include "../graphics/Mesh.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class TextBuilder
      {
      private:
        const Font* font;
        const gdu::String* string;
        float size;
        float maxLineSize;
        bool centered;

        float cx;
        float cy;

        ArrayList<unsigned int> indices;
        ArrayList<float> positions;
        ArrayList<float> uvs;

        void buildCharQuad(float, float, float, float, float, float, float, float);
        void buildChar(char);
        void buildLine(const Line&);
      public:
        TextBuilder(const Font*, const gdu::String*, float, float, bool);
        TextBuilder(const TextBuilder&);
        TextBuilder& operator=(const TextBuilder&);

        void build();
        void loadMesh(gdg::Mesh*) const;
      };
    }
  }
}

#endif
