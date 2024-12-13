#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <QOpenGLFunctions>
#include <QDebug>
#include "affine_matrix.h"
#include "coor_for_paint.h"


struct ModelData {
    std::vector<Vertex> vertices; //Vertex
    std::vector<Texture_coordinat> textureCoords; //Texture coordinates
    std::vector<Normal> normals; //Normals
    std::vector<Face> faces; // Edges
};

class Model {
public:
    Model() {}

    bool parseObjFile(const std::string &filename);
    ModelData* getModelData() { return modelData; }
    void move_figure(float x, float y, float z);
    void scaling_figure(float x, float y, float z);
    void rotate_figure(float x, float y, float z);

public:
    ModelData* modelData;

};

#endif // MODEL_H
