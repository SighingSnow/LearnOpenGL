//   #define TINYOBJLOADER_IMPLEMENTATION
#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <glm/glm.hpp>
#include "mesh.h"

class Model 
{
public:
    Model(std::string filename,std::string directory);
    void draw(const Shader & shader) const;
private:
    std::vector<Mesh> meshes;
    void loadModel(std::string filename,std::string directory);
    void convert2vec2(const std::vector<float> & vec, std::vector<glm::vec2> & res);
    void convert2vec3(const std::vector<float> & vec, std::vector<glm::vec3> & res);
};

#endif