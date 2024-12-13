#ifndef COOR_FOR_PAINT_H
#define COOR_FOR_PAINT_H
#include <iostream>
struct Vertex {
    float x, y, z;
};
struct Texture_coordinat {
    float u, v;
};
struct Normal {
    float nx, ny, nz;
};
struct Face {
    std::vector<int> vertexIndices; 
    std::vector<int> texCoordIndices;  
    std::vector<int> normalIndices;  
};

#endif //COOR_FOR_PAINT_H
