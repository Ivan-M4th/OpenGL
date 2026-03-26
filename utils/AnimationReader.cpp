#include "AnimationReader.h"

#include "Utilities.h"
#include "../math/Matrix4x4.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      AnimationReader::AnimationReader(XMLNode* file, const ArrayList<String>* idNames)
      {
        this->file = file;
        this->idNames = idNames;

        jointAnimations.setSize(idNames->size());
        jointAnimations.trim();
      }

      void AnimationReader::getLocationId(const String& idName, bool* containsName, unsigned int* id) const
      {
        *containsName = false;
        for(unsigned int i=0;i<idNames->size();i++)
        {
          if((*idNames)[i] == idName)
          {
            *containsName = true;
            *id = i;
            return;
          }
        }
      }

      void AnimationReader::readSource(const XMLNode& node, const String& dataType, String* source) const
      {
        *source = node.getByAttribute("input", "semantic", dataType).getAttribute("source").replace("#", "");
      }

      void AnimationReader::readJointAnimation(const XMLNode& node)
      {
        String idName = node["channel"].getAttribute("target").split("/")[0];
        std::cout << "reading animation of joint " << idName << std::endl;

        bool containsName;
        unsigned int id;
        getLocationId(idName, &containsName, &id);
        if(containsName)
        {
          std::cout << "loading animation for: " << idName << ", id: " << id << std::endl;
          String inputSource;
          String outputSource;

          readSource(node["sampler"], "INPUT", &inputSource);
          readSource(node["sampler"], "OUTPUT", &outputSource);

          ArrayList<float> timeStamps = node.getByAttribute("source", "id", inputSource)["float_array"].getData().toList<float>(" ");
          ArrayList<gdm::Matrix4x4> transformations = toMatrix4x4Array(node.getByAttribute("source", "id", outputSource)["float_array"].getData());

          jointAnimations[id] = gdga::JointAnimation(timeStamps, transformations);
        }
      }

      void AnimationReader::readJointAnimations(const XMLNode& node)
      {
        const ArrayList<const XMLNode*> children = node.getChildren("animation");
        for(unsigned int i=0;i<children.size();i++)
        {
          readJointAnimation(*children[i]);
        }
      }

      gdga::Animation AnimationReader::read()
      {
        readJointAnimations((*file)["COLLADA"]["library_animations"]["animation"]);
        return gdga::Animation(jointAnimations);
      }
    }
  }
}
