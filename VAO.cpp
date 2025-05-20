#include "VAO.h"

VAO::VAO()
{
  glGenVertexArrays(1, &ID); // Generate VAO ID
}

void VAO::LinkAttrib(VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void *offset)
{
  vbo.Bind();                                                                   // Bind the VBO
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); // Link the VBO to the VAO
  glEnableVertexAttribArray(layout);                                            // Enable the attribute
  vbo.Unbind();                                                                 // Unbind the VBO
}

void VAO::Bind()
{
  glBindVertexArray(ID); // Bind the VAO
}

void VAO::Unbind()
{
  glBindVertexArray(0); // Unbind the VAO
}

void VAO::Delete()
{
  glDeleteVertexArrays(1, &ID); // Delete the VAO
}