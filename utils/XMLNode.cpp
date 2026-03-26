#include "XMLNode.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      XMLNode::XMLNode()
      {
        name = "XML_FILE_CONTAINER";
      }

      XMLNode::XMLNode(const String& name, const ArrayList<XMLAttribute>& attributes)
      {
        this->name = name;
        this->attributes = attributes;
      }

      XMLNode::XMLNode(const String& name, const ArrayList<XMLAttribute>& attributes, const String& data)
      {
        this->name = name;
        this->attributes = attributes;
        this->data = data;
      }

      XMLNode::XMLNode(const XMLNode& node)
      {
        name = node.name;
        attributes = node.attributes;
        data = node.data;
        copyChildren(node);
      }

      XMLNode& XMLNode::operator=(const XMLNode& node)
      {
        deleteData();
        name = node.name;
        attributes = node.attributes;
        data = node.data;
        copyChildren(node);
        return *this;
      }

      XMLNode::~XMLNode()
      {
        deleteData();
      }

      void XMLNode::addChild(XMLNode* node)
      {
        children.add(node);
      }

      void XMLNode::deleteData()
      {
        for(unsigned int i=0;i<children.size();i++)
        {
          delete children[i];
        }
        children.clear();
      }

      void XMLNode::copyChildren(const XMLNode& node)
      {
        for(unsigned int i=0;i<node.children.size();i++)
        {
          addChild(new XMLNode(*node.children[i]));
        }
      }

      const String& XMLNode::getName() const
      {
        return name;
      }

      const String& XMLNode::getAttribute(const String& chars) const
      {
        for(unsigned int i=0;i<attributes.size();i++)
        {
          if(attributes[i].getName() == chars)
          {
            return attributes[i].getValue();
          }
        }
        assert(false && "attribute not found!");
      }

      const String& XMLNode::getData() const
      {
        return data;
      }

      const ArrayList<XMLNode*>& XMLNode::getChildren() const
      {
        return children;
      }

      const ArrayList<const XMLNode*> XMLNode::getChildren(const String& name) const
      {
        ArrayList<const XMLNode*> res;
        for(unsigned int i=0;i<children.size();i++)
        {
          if(children[i]->getName() == name)
          {
            res.add(children[i]);
          }
        }
        return res;
      }

      const XMLNode& XMLNode::operator[](const char* chars) const
      {
        for(unsigned int i=0;i<children.size();i++)
        {
          if(children[i]->getName() == chars)
          {
            return *children[i];
          }
        }
        assert(false && "child not found!");
      }

      const XMLNode& XMLNode::getByAttribute(const String& name, const String& attribute, const String& value) const
      {
        for(unsigned int i=0;i<children.size();i++)
        {
          if(children[i]->getName() == name)
          {
            if(children[i]->getAttribute(attribute) == value)
            {
              return *children[i];
            }
          }
        }
        assert(false && "child not found!");
      }
    }
  }
}
