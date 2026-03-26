#include "XMLReader.h"

#include <iostream>
#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      XMLReader::XMLReader(const char* fileName)
      {
        file = fileToString(fileName);
        index = 0;
      }

      XMLReader::XMLReader(const XMLReader& reader)
      {
        file = reader.file;
        index = reader.index;
      }

      XMLReader& XMLReader::operator=(const XMLReader& reader)
      {
        file = reader.file;
        index = reader.index;
        return *this;
      }

      XMLNode XMLReader::read()
      {
        XMLNode node;
        skipToNext('<');
        while(isValid())
        {
          node.addChild(readNode());
          skipToNext('<');
        }
        return node;
      }

      bool XMLReader::isValid() const
      {
        return index < file.size();
      }

      void XMLReader::ignore(char c)
      {
        while(isValid())
        {
          if(file[index] == c)
          {
            index++;
          }
          else
          {
            break;
          }
        }
      }

      void XMLReader::skipToNext(char c)
      {
        while(isValid())
        {
          if(file[index] == c)
          {
            break;
          }
          else
          {
            index++;
          }
        }
      }

      void XMLReader::skipToNextVisibleChar()
      {
        while(isValid())
        {
          char c = file[index];
          if(isprint(c) && c != ' ')
          {
            return;
          }
          index++;
        }
      }

      bool XMLReader::isEndOfNode(const String& name) const
      {
        if(index + 2 + name.size() >= file.size())
        {
          return false;
        }

        if(file[index] != '<')
        {
          return false;
        }
        if(file[index + 1] != '/')
        {
          return false;
        }

        for(unsigned int k = 0;k<name.size();k++)
        {
          if(file[index + 2 + k] != name[k])
          {
            return false;
          }
        }
        return file[index + 2 + name.size()] == '>';
      }

      void XMLReader::readNodeName(String* name)
      {
        char c = file[index];
        while(isValid())
        {
          if(c == ' ' || c == '>' || c == '/')
          {
            break;
          }
          else
          {
            name->addChar(c);
            index++;
            c = file[index];
          }
        }
      }

      String XMLReader::readAttributeName()
      {
        String result;
        char c = file[index];
        while(isValid())
        {
          if(c == '=')
          {
            break;
          }
          else
          {
            result.addChar(c);
            index++;
            c = file[index];
          }
        }
        assert(c == '=');
        index++;
        return result;
      }

      String XMLReader::readAttributeValue()
      {
        skipToNext('\"');
        index++;
        assert(isValid());

        String result;
        char c = file[index];
        while(isValid())
        {
          if(c == '\"')
          {
            break;
          }
          else
          {
            result.addChar(c);
            index++;
            c = file[index];
          }
        }

        assert(isValid());
        assert(c == '\"');
        index++;
        return result;
      }

      XMLAttribute XMLReader::readAttribute()
      {
        String name = readAttributeName();
        String value = readAttributeValue();

        std::cout << "attribute name: " << name << std::endl;
        std::cout << "attribute value: " << value << std::endl;
        return XMLAttribute(name, value);
      }

      bool XMLReader::readNodeHeader(String* name, ArrayList<XMLAttribute>* attributes)
      {
        readNodeName(name);
        std::cout << "name: " << *name << std::endl;
        assert(isValid());

        char c = file[index];
        while(c == ' ')
        {
          ignore(' ');
          XMLAttribute attribute = readAttribute();
          attributes->add(attribute);

          assert(isValid());
          c = file[index];
        }
        ignore(' ');

        bool exitNode = false;
        if(c == '/')
        {
          exitNode = true;
          index++;
          c = file[index];
        }
        assert(c == '>');
        index++;

        return exitNode;
      }

      XMLNode* XMLReader::readNode()
      {
        skipToNext('<');
        index++;
        assert(isValid());
        std::cout << "skiped to: " << index << std::endl;

        String name;
        ArrayList<XMLAttribute> attributes;

        XMLNode* node = NULL;
        if(!readNodeHeader(&name, &attributes))
        {
          std::cout << file[index] << std::endl;
          skipToNextVisibleChar();
          std::cout << file[index] << std::endl;

          assert(isValid());

          if(file[index] == '<')
          {
            node = new XMLNode(name, attributes);
            readChildrenNodes(node);
          }
          else
          {
            node = new XMLNode(name, attributes, readNodeData());
          }
          assert(isEndOfNode(name) && "Error node format incorrect!");
          index+= 3 + name.size();
        }
        else
        {
          node = new XMLNode(name, attributes);
        }
        std::cout << "done reading node: " << name << std::endl;
        return node;
      }

      void XMLReader::readChildrenNodes(XMLNode* node)
      {
        while(isValid())
        {
          node->addChild(readNode());
          skipToNext('<');
          std::cout << "checking if is end of: " << node->getName() << std::endl;
          if(isEndOfNode(node->getName()))
          {
            break;
          }
        }
      }

      String XMLReader::readNodeData()
      {
        String data;
        while(isValid())
        {
          char c = file[index];
          if(c == '<')
          {
            break;
          }
          data.addChar(c);
          index++;
        }
        std::cout << "data: " << data << std::endl;
        return data;
      }
    }
  }
}
