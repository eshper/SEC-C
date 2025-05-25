#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:
  GLuint ID;
  std::string type;
  GLuint unit;
  std::string path;

  Texture(const char *image, const char *texType, GLuint slot);

  void TexUnit(Shader &shader, const char *uniform, GLuint unit);
  void Bind();
  void Unbind();
  void Delete();
};

#endif // TEXTURE_H