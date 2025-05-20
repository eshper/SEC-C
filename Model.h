#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
  Model(char *path);
  void Draw(Shader &shader, Camera &camera);

private:
  std::vector<Mesh> meshes;
  std::vector<std::string> loadedTexName;
  std::vector<Texture> loadedTex;
  std::string directory;

  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, int &numTextures);
};

#endif // MODEL_H