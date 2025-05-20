#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  vao.Bind();
  VBO vbo(vertices);
  EBO ebo(indices);

  // print all vertex attribute data
  // for (int i = 0; i < vertices.size(); i++)
  // {
  //   std::cout << "Vertex " << i << ": ";
  //   std::cout << "Position: (" << vertices[i].position.x << ", " << vertices[i].position.y << ", " << vertices[i].position.z << "), ";
  //   std::cout << "Normal: (" << vertices[i].normal.x << ", " << vertices[i].normal.y << ", " << vertices[i].normal.z << "), ";
  //   std::cout << "Color: (" << vertices[i].color.x << ", " << vertices[i].color.y << ", " << vertices[i].color.z << "), ";
  //   std::cout << "TexCoords: (" << vertices[i].texCoords.x << ", " << vertices[i].texCoords.y << ")" << std::endl;
  // }

  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);                   // position
  vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(float) * 3)); // normal
  vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(float) * 6)); // color
  vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(float) * 9)); // texCoords

  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera)
{
  shader.Activate();
  vao.Bind();

  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;

  for (unsigned int i = 0; i < textures.size(); i++)
  {
    std::string num;
    std::string type = textures[i].type;
    if (type == "diffuse")
    {
      num = std::to_string(numDiffuse++);
    }
    else if (type == "specular")
    {
      num = std::to_string(numSpecular++);
    }

    std::string uniformName = type + num;
    // std::cout << "Binding texture " << i << " as " << uniformName << std::endl;

    textures[i].TexUnit(shader, (type + num).c_str(), i);
    textures[i].Bind();
  }

  glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
  camera.Matrix(shader, "camMatrix");

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}