#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
public:
  GLuint ID;
  Shader(const char *vertexPath, const char *fragmentPath);

  void Activate();
  void Delete();
};

#endif // SHADER_H