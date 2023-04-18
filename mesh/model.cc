#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../tiny_obj_loader.h"
Model::Model(std::string filename,std::string directory)
{
    loadModel(filename,directory);
    // TODO: construct a shader
}

void Model::draw(const Shader & shader) const {
    for (const auto & mesh : meshes) {
        mesh.draw(shader);
    }
}

void Model::loadModel(std::string filename,std::string directory)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn,err;
    // True means triangulate the faces
    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials,
        &warn, 
        &err,
        filename.c_str(), //model to load
        directory.c_str(), //directory to search for materials
        true); //enable triangulation
    if (!success) {
        std::cerr<<err<<std::endl;
        return;
    }
    if (!warn.empty()) {
        std::cout<<warn<<std::endl;
    }
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // construct vertex
    convert2vec2(attrib.texcoords,tex_coords);
    convert2vec3(attrib.normals,normals);
    convert2vec3(attrib.vertices,positions);
    // push back vertices
   
    //std::cout<<"positions size: "<<positions.size()<< " normal size: "<<normals.size()<<" tex size: "<<tex_coords.size()<<std::endl;
    for(int i = 0; i < positions.size();i++) {
        Vertex v;
        v.position = positions[i];
        v.normal = i < normals.size() ? normals[i] : glm::vec3(0,0,0);
        v.texCoords = i < tex_coords.size() ? tex_coords[i] : glm::vec2(0,0);
        vertices.push_back(v);
    }
    // push back indices
    for(const auto & shape : shapes) {
        for(int j = 0; j < shape.mesh.indices.size();j++) {
            indices.push_back(shape.mesh.indices[j].vertex_index);
        }
    }
    Mesh * mesh = new Mesh(vertices,indices,textures);
    meshes.push_back(*mesh);
    return ;
}

void Model::convert2vec2(const std::vector<float> & vec, std::vector<glm::vec2> & res)
{
    for(int i = 0;i < vec.size();i+=2) {
        res.emplace_back(vec[i],vec[i+1]);
    }
    return;
}
void Model::convert2vec3(const std::vector<float> & vec, std::vector<glm::vec3> & res)
{
    for(int i = 0;i < vec.size();i+=3) {
        res.emplace_back(vec[i],vec[i+1],vec[i+2]);
    }
    return;
}