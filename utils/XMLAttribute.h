#ifndef GD_UTILS_XMLATTRIBUTE_H
#define GD_UTILS_XMLATTRIBUTE_H

#include "String.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLAttribute
      {
      private:
        String name;
        String value;

      public:
        XMLAttribute();
        XMLAttribute(const String&, const String&);
        XMLAttribute(const XMLAttribute&);
        XMLAttribute& operator=(const XMLAttribute&);

        const String& getName() const;
        const String& getValue() const;
      };
    }
  }
}

#endif
