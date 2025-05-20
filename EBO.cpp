#include "EBO.h"

EBO::EBO(std::vector<GLuint> &indices)
{
  glGenBuffers(1, &ID);                                                                                   // Generate buffer ID
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);                                                              // Bind the buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW); // Allocate memory and copy data
}

void EBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // Bind the buffer
}

void EBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer
}

void EBO::Delete()
{
  glDeleteBuffers(1, &ID); // Delete the buffer
}