#ifndef GD_UTILS_XMLREADER_H
#define GD_UTILS_XMLREADER_H

#include "String.h"
#include "ArrayList.h"
#include "XMLAttribute.h"
#include "XMLNode.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLReader
      {
      private:
        String file;
        unsigned int index;

        bool isValid() const;
        void ignore(char);
        void skipToNext(char);
        void skipToNextVisibleChar();
        bool isEndOfNode(const String&) const;

        void readNodeName(String*);
        String readAttributeName();
        String readAttributeValue();
        XMLAttribute readAttribute();
        bool readNodeHeader(String*, ArrayList<XMLAttribute>*);
        XMLNode* readNode();
        void readChildrenNodes(XMLNode*);
        String readNodeData();
      public:
        XMLReader(const char*);
        XMLReader(const XMLReader&);
        XMLReader& operator=(const XMLReader&);

        XMLNode read();
      };
    }
  }
}

#endif
