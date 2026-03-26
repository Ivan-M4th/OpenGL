#include "XMLAttribute.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      XMLAttribute::XMLAttribute()
      {

      }

      XMLAttribute::XMLAttribute(const String& name, const String& value)
      {
        this->name = name;
        this->value = value;
      }

      XMLAttribute::XMLAttribute(const XMLAttribute& attribute)
      {
        name = attribute.name;
        value = attribute.value;
      }

      XMLAttribute& XMLAttribute::operator=(const XMLAttribute& attribute)
      {
        name = attribute.name;
        value = attribute.value;
        return *this;
      }

      const String& XMLAttribute::getName() const
      {
        return name;
      }

      const String& XMLAttribute::getValue() const
      {
        return value;
      }
    }
  }
}
