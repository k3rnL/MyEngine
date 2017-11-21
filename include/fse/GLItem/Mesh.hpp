/**
 * @Author: daniel_b
 * @Date:   2017-08-19T19:54:53+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-11-20T23:29:54+01:00
 */



#ifndef MXE_GL_MESH
#define MXE_GL_MESH

#include <vector>
#include <map>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>

#include "fse/GLItem/Shader.hpp"
#include "fse/ShaderManager.hpp"

namespace fse {
  namespace gl_item {

    class Mesh
    {
    public:
      Mesh();

      Mesh(Mesh &mesh);
      ~Mesh() {};

      void          addAll(const glm::vec3 &vertex, const glm::vec3 &normal, const glm::vec2 &uv);
      size_t        addVertex(const glm::vec3 &vertex);
      size_t        addTangent(const glm::vec3 &vertex);
      size_t        addBitangent(const glm::vec3 &vertex);
      size_t        addFace(const glm::vec3 &indices);
      size_t        addNormal(const glm::vec3 &normal);
      size_t        addUV(const glm::vec2 &uv);
      void          finish();

      std::vector<glm::vec3>      &getVertexes();
      std::vector<glm::vec3>      &getNormals();
      std::vector<glm::vec2>      &getUVs();
      std::vector<unsigned int>   &getIndices();

      void          clear();
      void          smoothNormal();
      void          genTangentSpace();
      void          genNormals();

      int         getElementCount();

      void        bindToShader(std::shared_ptr<gl_item::Shader> shader);
      void        detachFromShader();

      size_t          _nb_vertex;

      
      glm::vec3                   _min;
      glm::vec3                   _max;
    private:
        std::shared_ptr<Shader>     _shader;

        std::vector<glm::vec3>        _mesh_tangents;
        std::vector<glm::vec3>        _mesh_bitangents;
      std::vector<glm::vec3>        _mesh_vertexes;
      std::vector<unsigned int>     _mesh_indices;
      std::vector<glm::vec3>        _mesh_normals;
      std::vector<glm::vec2>        _mesh_uvs;

      Buffer          _buffer_vertex;
      Buffer          _buffer_tangent;
      Buffer          _buffer_bitangent;
      Buffer          _buffer_indices;
      Buffer          _buffer_normal;
      Buffer          _buffer_uv;

      void            enableAttribute(GLuint buffer, GLuint attr, GLuint size, GLint buffer_type = GL_ARRAY_BUFFER);
      void            clearGPU();
    };

  }
}

#endif
