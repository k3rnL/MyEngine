/**
 * @Author: daniel_b
 * @Date:   2017-08-19T19:54:53+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-08-30T05:15:03+02:00
 */



#ifndef MXE_GL_MESH
#define MXE_GL_MESH

#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include "Shader.hpp"
#include "Mxe/ShaderManager.hpp"

namespace mxe {
  namespace gl_item {

    class Mesh
    {
    public:
      Mesh();
      ~Mesh() {};

      void        addAll(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv);
      void        addVertex(const glm::vec3 &vertex);
      void        addNormal(const glm::vec3 &normal);
      void        addUV(const glm::vec2 &uv);
      void        finish();

      void        bindToShader();
      void        detachFromShader();

      size_t          _nb_vertex;

    private:

      std::vector<glm::vec3>  _mesh_vertexes;
      std::vector<glm::vec3>  _mesh_normals;
      std::vector<glm::vec2>  _mesh_uvs;

      GLuint          _buffer_vertex_id;
      GLuint          _buffer_normal_id;
      GLuint          _buffer_uv_id;
      GLsizei         _buffer_size;

      void            enableAttribute(GLuint buffer, GLuint attr, GLuint size);
    };

  }
}

#endif
