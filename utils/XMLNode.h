#ifndef GD_UTILS_XMLNODE_H
#define GD_UTILS_XMLNODE_H

#include "String.h"
#include "ArrayList.h"
#include "XMLAttribute.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLNode
      {
      private:
        String name;
        ArrayList<XMLAttribute> attributes;
        String data;

        ArrayList<XMLNode*> children;

        void deleteData();
        void copyChildren(const XMLNode&);

      public:
        XMLNode();
        XMLNode(const String&, const ArrayList<XMLAttribute>&);
        XMLNode(const String&, const ArrayList<XMLAttribute>&, const String&);
        XMLNode(const XMLNode&);
        XMLNode& operator=(const XMLNode&);
        ~XMLNode();

        void addChild(XMLNode*);

        const String& getName() const;
        const String& getAttribute(const String&) const;
        const String& getData() const;
        const ArrayList<XMLNode*>& getChildren() const;
        const ArrayList<const XMLNode*> getChildren(const String&) const;

        const XMLNode& operator[](const char*) const;
        const XMLNode& getByAttribute(const String&, const String&, const String&) const;
      };
    }
  }
}

#endif
