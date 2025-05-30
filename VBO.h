#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 texCoords;
};

class VBO
{
public:
  GLuint ID;
  VBO(std::vector<Vertex> &vertices);

  void Bind();
  void Unbind();
  void Delete();
};

#endif // VBO_CLASS_H