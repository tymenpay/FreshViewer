#ifndef AFFINE_MATRIX_H
#define AFFINE_MATRIX_H

#include "coor_for_paint.h"

struct Matrix4x4 {
    float m[4][4];
    Matrix4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = 0.0f;
            }
        }
    }
};
struct Affine_matrix {
    Matrix4x4 translation(float tx, float ty, float tz) {
        Matrix4x4 m;
        m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1;
        m.m[0][3] = tx;
        m.m[1][3] = ty;
        m.m[2][3] = tz;
        return m;
    }
    Matrix4x4 rotationX(float angle) {
        Matrix4x4 m;
        m.m[0][0] = m.m[3][3] = 1;
        m.m[1][1] = cos(angle);
        m.m[1][2] = -sin(angle);
        m.m[2][1] = sin(angle);
        m.m[2][2] = cos(angle);
        return m;
    }
    Matrix4x4 rotationY(float angle) {
        Matrix4x4 m;
        m.m[0][0] = cos(angle);
        m.m[0][2] = -sin(angle);
        m.m[1][1] = 1;
        m.m[2][0] = sin(angle);
        m.m[2][2] = cos(angle);
        m.m[3][3] = 1;
        return m;
    }
    Matrix4x4 rotationZ(float angle) {
        Matrix4x4 m;
        m.m[0][0] = cos(angle);
        m.m[0][1] = -sin(angle);
        m.m[1][0] = sin(angle);
        m.m[1][1] = cos(angle);
        m.m[2][2] = 1;
        m.m[3][3] = 1;
        return m;
    }
    Matrix4x4 scale(float sx, float sy, float sz) {
        Matrix4x4 m;
        m.m[0][0] = sx;
        m.m[1][1] = sy;
        m.m[2][2] = sz;
        m.m[3][3] = 1;
        return m;
    }
    Vertex scaling(Vertex v, Matrix4x4 m) {
        Vertex res;
        res.x = v.x * m.m[0][0];
        res.y = v.y * m.m[1][1];
        res.z = v.z * m.m[2][2];
        return res;
    }
    Vertex translate(Vertex v, Matrix4x4 m) {
        Vertex res;
        res.x = v.x + m.m[0][3];
        res.y = v.y + m.m[1][3];
        res.z = v.z + m.m[2][3];
        return res;
    }
    Vertex rotateX(Vertex v, Matrix4x4 m) {
        Vertex res;
        res.y = v.y * m.m[1][1] + v.z * m.m[1][2];
        res.z = v.y * m.m[2][1] + v.z * m.m[2][2];
        res.x = v.x;
        return res;
    }
    Vertex rotateY(Vertex v, Matrix4x4 m) {
        Vertex res;
        res.x = v.x * m.m[0][0] + v.z * m.m[0][2];
        res.y = v.y;
        res.z = v.x * m.m[2][0] + v.z * m.m[2][2];
        return res;
    }
    Vertex rotateZ(Vertex v, Matrix4x4 m) {
        Vertex res;
        res.x = v.x * m.m[0][0] + v.y * m.m[0][1];
        res.y = v.x * m.m[1][0] + v.y * m.m[1][1];
        res.z = v.z;
        return res;
    }
};
#endif //AFFINE_MATRIX_H
