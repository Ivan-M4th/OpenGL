#include "ArmatureReader.h"

#include <cassert>

#include "../gddef.h"

#include "Utilities.h"

#include "../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      ArmatureReader::ArmatureReader()
      {
        file = NULL;
      }

      ArmatureReader::ArmatureReader(XMLNode* file, const ArrayList<String>* jointNames)
      {
        this->file = file;
        this->jointNames = jointNames;

        idNames.setSize(jointNames->size());
      }

      ArmatureReader::ArmatureReader(const ArmatureReader& reader)
      {
        file = reader.file;
        jointNames = reader.jointNames;

        idNames = reader.idNames;
      }

      ArmatureReader& ArmatureReader::operator=(const ArmatureReader& reader)
      {
        file = reader.file;
        jointNames = reader.jointNames;

        idNames = reader.idNames;

        return *this;
      }

      const ArrayList<String>& ArmatureReader::getIdNames() const
      {
        return idNames;
      }

      unsigned int ArmatureReader::getId(const String& name) const
      {
        std::cout << "searching for id of " << name << std::endl;
        for(unsigned int i=0;i<jointNames->size();i++)
        {
          if((*jointNames)[i] == name)
          {
            return i;
          }
        }

        assert(false && "error joint name not found!");
      }

      gdga::Joint* ArmatureReader::readJoint(const XMLNode& node)
      {
        String name = node.getAttribute("sid");
        String idName = node.getAttribute("id");
        gdm::Matrix4x4 transformation = toMatrix4x4(node["matrix"].getData());
        unsigned int id = getId(name);
        idNames[id] = idName;

        std::cout << "reading joint: " << id << " : " << name << " : " << idName << std::endl;

        gdga::Joint* joint = new gdga::Joint(id, name, transformation);

        const ArrayList<const XMLNode*> nodeChildren = node.getChildren("node");
        for(unsigned int i=0;i<nodeChildren.size();i++)
        {
          gdga::Joint* child = readJoint(*nodeChildren[i]);
          joint->children.add(child);
        }

        std::cout << "done reading joint: " << id << " : " << name << " : " << idName << std::endl;
        return joint;
      }

      gdga::Armature ArmatureReader::read()
      {
        gdga::Joint* joint = readJoint((*file)["COLLADA"]["library_visual_scenes"]["visual_scene"]["node"]["node"]);
        joint->calculateInverseDefaultTransformation(gdm::Matrix4x4());
        return gdga::Armature(jointNames->size(), joint);
      }
    }
  }
}
