#include "Texture.h"
#include <iostream>

Texture::Texture(const char *image, const char *texType, GLuint slot)
{
  std::cout << "Loading texture: " << image << std::endl;
  std::cout << texType << slot << std::endl;
  this->type = std::string(texType);

  int widthImg, heightImg, numColCh;
  stbi_set_flip_vertically_on_load(true); // Flip the image vertically
  unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

  glGenTextures(1, &ID);
  glActiveTexture(GL_TEXTURE0 + slot);
  unit = slot;
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  std::cout << "Channels in " << image << ": " << numColCh << std::endl;
  if (numColCh == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
  else if (numColCh == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
  else if (numColCh == 1)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
  else
    throw "ERROR::TEXTURE::TEXTURE: Texture format not supported!";

  // unsigned char checkerboard[64 * 64 * 3]; // 64x64, RGB

  // for (int y = 0; y < 64; y++)
  // {
  //   for (int x = 0; x < 64; x++)
  //   {
  //     int pixelIndex = (y * 64 + x) * 3;
  //     bool isWhite = ((x / 8 + y / 8) % 2) == 0;

  //     if (isWhite)
  //     {
  //       checkerboard[pixelIndex + 0] = 255; // R
  //       checkerboard[pixelIndex + 1] = 255; // G
  //       checkerboard[pixelIndex + 2] = 255; // B
  //     }
  //     else
  //     {
  //       checkerboard[pixelIndex + 0] = 0;
  //       checkerboard[pixelIndex + 1] = 0;
  //       checkerboard[pixelIndex + 2] = 0;
  //     }
  //   }
  // }

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, checkerboard);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(bytes);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TexUnit(Shader &shader, const char *uniform, GLuint unit)
{
  GLuint texUni = glGetUniformLocation(shader.ID, uniform);
  shader.Activate();
  glUniform1i(texUni, unit);
}

void Texture::Bind()
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
  glDeleteTextures(1, &ID);
}