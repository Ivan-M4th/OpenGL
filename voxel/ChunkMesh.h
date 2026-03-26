#ifndef GD_VOXEL_CHUNKMESH_H
#define GD_VOXEL_CHUNKMESH_H

#include "../gddef.h"

#include "../graphics/Mesh.h"
#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ChunkMesh
      {
      private:
        gdg::Mesh mesh;

        bool loaded;
      public:
        ChunkMesh();
        ChunkMesh(const ChunkMesh&);
        ChunkMesh& operator=(const ChunkMesh&);

        void deleteData();
        void loadData(const ArrayList<float>&, const ArrayList<float>&, const ArrayList<float>&, const ArrayList<unsigned int>&);

        gdg::Mesh* getMesh();
        bool isLoaded() const;
      };
    }
  }
}

#endif
