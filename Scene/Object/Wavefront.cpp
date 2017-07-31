/**
 * @Author: daniel_b
 * @Date:   2017-07-25T00:33:51+02:00
 * @Last modified by:   daniel_b
 * @Last modified time: 2017-07-31T04:35:23+02:00
 */



#include "Wavefront.hpp"

using namespace mxe::scene::object;

Wavefront::Wavefront(const std::string &file) :
    _file_name(file)
{
  std::ifstream             file_stream(file);
  std::string               line;

  std::vector<glm::vec3>    vertices;
  std::vector<glm::vec3>    normals;

  std::vector<glm::vec3>    mesh;
  std::vector<glm::vec3>    mesh_normal;

  while (std::getline(file_stream, line))
  {
    if (line[0] == 'v')
      {
        std::istringstream  ss(line.substr(2));
        double              value;
        glm::vec3           vertex;

        for (int i = 0 ; i < 3 ; i++)
          {
            ss >> value;
            vertex[i] = value;
          }
        vertices.push_back(vertex);
      }
    if (line.compare(0, 2, "vn") == 0)
    {
      std::istringstream  ss(line.substr(2));
      double              value;
      glm::vec3           vertex;

      for (int i = 0 ; i < 3 ; i++)
        {
          ss >> value;
          vertex[i] = value;
        }
      normals.push_back(vertex);
    }
    if (line[0] == 'f')
    {
      std::istringstream  ss(line.substr(2));
      std::string         token;

      while (ss >> token)
      {
        std::istringstream  ss(token);
        std::string         index;
        int                 i = 0;

        while (std::getline(ss, index, '/'))
        {
          if (i == 0)
            mesh.push_back(vertices[std::stoi(index) - 1]);
          if (i == 2 && index.size())
            mesh_normal.push_back(normals[std::stoi(index) - 1]);
          i++;
        }
      }

    }
  }

  glGenBuffers(1, &_buffer_vertex_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_vertex_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * mesh.size() , &mesh[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_buffer_normal_id);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_normal_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (glm::vec3) * mesh_normal.size() , &mesh_normal[0], GL_STATIC_DRAW);

  _buffer_size = sizeof (glm::vec3) * mesh.size();

  _nb_vertex = mesh.size();

  _material.setColor(0.8, 1, 1);
  _material.applyMaterial(); // Also call glUseProgram()
}

mxe::scene::INode       *Wavefront::clone()
{
    Wavefront           *node = new Wavefront(_file_name);

    node->position = position;
    node->rotation = rotation;
    return (node);
}
