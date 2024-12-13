#include "3DModel.h"

bool Model::parseObjFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    bool error = true;
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
        error = false;
    }
    if (!modelData) {
        modelData = new ModelData();
    }

    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            float x, y, z;
            std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
            Vertex vertex;
            vertex.x = x;
            vertex.y = y;
            vertex.z = z;
            modelData->vertices.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vt ") {
            float u, v;
            std::sscanf(line.c_str(), "vt %f %f", &u, &v);
            modelData->textureCoords.push_back(Texture_coordinat{u, v});
        }
        else if (line.substr(0, 3) == "vn ") {
            float nx, ny, nz;
            std::sscanf(line.c_str(), "vn %f %f %f", &nx, &ny, &nz);
            modelData->normals.push_back(Normal{nx, ny, nz});
        }
        else if (line.substr(0, 1) == "f") {
            std::istringstream faceStream(line);
            std::string faceToken;
            Face face;

            faceStream >> faceToken;

            while (faceStream >> faceToken) {
                std::replace(faceToken.begin(), faceToken.end(), '/', ' ');
                std::istringstream tokenStream(faceToken);
                int vertexIndex, texCoordIndex, normalIndex;

                tokenStream >> vertexIndex >> texCoordIndex >> normalIndex;

                face.vertexIndices.push_back(vertexIndex - 1);
                face.texCoordIndices.push_back(texCoordIndex - 1);
                face.normalIndices.push_back(normalIndex - 1);
            }
            modelData->faces.push_back(face);
        }
    }

    file.close();
    return error;
}

void Model::move_figure(float x, float y, float z) {
    Affine_matrix m;
    Matrix4x4 matrix_traslation = m.translation(x, y,z);
    for(auto &vertex : modelData->vertices) {
        vertex = m.translate(vertex, matrix_traslation);
    }
}
void Model::scaling_figure(float x, float y, float z) {
    if(x == 0) x = 1;
    if(y == 0) y = 1;
    if(z == 0) z = 1;
    Affine_matrix m;
    Matrix4x4 matrix_scale = m.scale(x, y,z);
    for(auto &vertex : modelData->vertices) {
        vertex = m.scaling(vertex, matrix_scale);
    }
}
void Model::rotate_figure( float x, float y, float z) {
    if(x!=0) {
        Affine_matrix mx;
        Matrix4x4 matrix_rotateX = mx.rotationX(x);
        for(auto &vertex : modelData->vertices) {
            vertex = mx.rotateX(vertex, matrix_rotateX);
        }
    }
    if(y!=0) {
        Affine_matrix my;
        Matrix4x4 matrix_rotateY = my.rotationY(y);
        for(auto &vertex : modelData->vertices) {
            vertex = my.rotateY(vertex, matrix_rotateY);
        }
    }
    if(z!=0) {
        Affine_matrix mz;
        Matrix4x4 matrix_rotateZ = mz.rotationZ(z);
        for(auto &vertex : modelData->vertices) {
            vertex = mz.rotateZ(vertex, matrix_rotateZ);
        }
    }
}




