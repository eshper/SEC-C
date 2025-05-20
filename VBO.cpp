#include "VBO.h"

VBO::VBO(std::vector<Vertex> &vertices)
{
  glGenBuffers(1, &ID);                                                                             // Generate buffer ID
  glBindBuffer(GL_ARRAY_BUFFER, ID);                                                                // Bind the buffer
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // Allocate memory and copy data
}

void VBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind the buffer
}

void VBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer
}

void VBO::Delete()
{
  glDeleteBuffers(1, &ID); // Delete the buffer
}