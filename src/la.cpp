#include "la.h"

//#define COL_MAJ   //Uncomment this line if you have made your matrices column-major

QMatrix4x4 la::to_qmat(const mat4 &m)
{
    float* val = new float[16];
#ifdef COL_MAJ
    val[0] = m[0][0]; val[1] = m[0][1]; val[2] = m[0][2]; val[3] = m[0][3];
    val[4] = m[1][0]; val[5] = m[1][1]; val[6] = m[1][2]; val[7] = m[1][3];
    val[8] = m[2][0]; val[9] = m[2][1]; val[10] = m[2][2]; val[11] = m[2][3];
    val[12] = m[3][0]; val[13] = m[3][1]; val[14] = m[3][2]; val[15] = m[3][3];
#else
    val[0] = m[0][0]; val[4] = m[0][1]; val[8] = m[0][2]; val[12] = m[0][3];
    val[1] = m[1][0]; val[5] = m[1][1]; val[9] = m[1][2]; val[13] = m[1][3];
    val[2] = m[2][0]; val[6] = m[2][1]; val[10] = m[2][2]; val[14] = m[2][3];
    val[3] = m[3][0]; val[7] = m[3][1]; val[11] = m[3][2]; val[15] = m[3][3];
#endif
    return QMatrix4x4(val);
}


QVector4D la::to_qvec(const vec4 &v){
    return QVector4D(v[0], v[1], v[2], v[3]);
}

mat4 la::inverse(mat4 M){
#ifdef COL_MAJ
    M = transpose(M);
#endif

    mat4 inverse;

    float a0 = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    float a1 = M[0][0]*M[1][2] - M[0][2]*M[1][0];
    float a2 = M[0][0]*M[1][3] - M[0][3]*M[1][0];
    float a3 = M[0][1]*M[1][2] - M[0][2]*M[1][1];
    float a4 = M[0][1]*M[1][3] - M[0][3]*M[1][1];
    float a5 = M[0][2]*M[1][3] - M[0][3]*M[1][2];
    float b0 = M[2][0]*M[3][1] - M[2][1]*M[3][0];
    float b1 = M[2][0]*M[3][2] - M[2][2]*M[3][0];
    float b2 = M[2][0]*M[3][3] - M[2][3]*M[3][0];
    float b3 = M[2][1]*M[3][2] - M[2][2]*M[3][1];
    float b4 = M[2][1]*M[3][3] - M[2][3]*M[3][1];
    float b5 = M[2][2]*M[3][3] - M[2][3]*M[3][2];
    float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

    if (det != 0){
        float invDet = 1.0f / det;
        vec4 r1(
        (+M[1][1]*b5 - M[1][2]*b4 + M[1][3]*b3)*invDet,
        (-M[0][1]*b5 + M[0][2]*b4 - M[0][3]*b3)*invDet,
        (+M[3][1]*a5 - M[3][2]*a4 + M[3][3]*a3)*invDet,
        (-M[2][1]*a5 + M[2][2]*a4 - M[2][3]*a3)*invDet);
        vec4 r2(
        (-M[1][0]*b5 + M[1][2]*b2 - M[1][3]*b1)*invDet,
        (+M[0][0]*b5 - M[0][2]*b2 + M[0][3]*b1)*invDet,
        (-M[3][0]*a5 + M[3][2]*a2 - M[3][3]*a1)*invDet,
        (+M[2][0]*a5 - M[2][2]*a2 + M[2][3]*a1)*invDet);
        vec4 r3(
        (+M[1][0]*b4 - M[1][1]*b2 + M[1][3]*b0)*invDet,
        (-M[0][0]*b4 + M[0][1]*b2 - M[0][3]*b0)*invDet,
        (+M[3][0]*a4 - M[3][1]*a2 + M[3][3]*a0)*invDet,
        (-M[2][0]*a4 + M[2][1]*a2 - M[2][3]*a0)*invDet);
        vec4 r4(
        (-M[1][0]*b3 + M[1][1]*b1 - M[1][2]*b0)*invDet,
        (+M[0][0]*b3 - M[0][1]*b1 + M[0][2]*b0)*invDet,
        (-M[3][0]*a3 + M[3][1]*a1 - M[3][2]*a0)*invDet,
        (+M[2][0]*a3 - M[2][1]*a1 + M[2][2]*a0)*invDet);
        inverse = mat4(r1, r2, r3, r4);
    }
    else{
        inverse = mat4();//zero matrix
        std::cout << "Determinant of matrix to invert was 0!" << std::endl;
    }
    #ifdef COL_MAJ
        inverse = transpose(inverse);
    #endif
    return inverse;
}

//Row major
float la::determinant2x2(const float(&m)[2][2]){
    return m[0][0]*m[1][1] - m[0][1]*m[1][0];
}

//Row major
float la::determinant3x3(const float(&m)[3][3]){
    float a1[2][2];
    a1[0][0] = m[1][1]; a1[0][1] = m[1][2];
    a1[1][0] = m[2][1]; a1[1][1] = m[2][2];
    float a2[2][2];
    a2[0][0] = m[1][0]; a2[0][1] = m[1][2];
    a2[1][0] = m[2][0]; a2[1][1] = m[2][2];
    float a3[2][2];
    a3[0][0] = m[1][0]; a3[0][1] = m[1][1];
    a3[1][0] = m[2][0]; a3[1][1] = m[2][1];
    return m[0][0]*determinant2x2(a1)
         - m[0][1]*determinant2x2(a2)
         + m[0][2]*determinant2x2(a3);
}

float la::determinant4x4(const mat4& m){
    float a1[3][3];
    a1[0][0] = m[1][1]; a1[0][1] = m[1][2]; a1[0][2] = m[1][3];
    a1[1][0] = m[2][1]; a1[1][1] = m[2][2]; a1[1][2] = m[2][3];
    a1[2][0] = m[3][1]; a1[2][1] = m[3][2]; a1[2][2] = m[3][3];

    float a2[3][3];
    a2[0][0] = m[1][0]; a2[0][1] = m[1][2]; a2[0][2] = m[1][3];
    a2[1][0] = m[2][0]; a2[1][1] = m[2][2]; a2[1][2] = m[2][3];
    a2[2][0] = m[3][0]; a2[2][1] = m[3][2]; a2[2][2] = m[3][3];

    float a3[3][3];
    a3[0][0] = m[1][0]; a3[0][1] = m[1][1]; a3[0][2] = m[1][3];
    a3[1][0] = m[2][0]; a3[1][1] = m[2][1]; a3[1][2] = m[2][3];
    a3[2][0] = m[3][0]; a3[2][1] = m[3][1]; a3[2][2] = m[3][3];

    float a4[3][3];
    a4[0][0] = m[1][0]; a4[0][1] = m[1][1]; a4[0][2] = m[1][2];
    a4[1][0] = m[2][0]; a4[1][1] = m[2][1]; a4[1][2] = m[2][2];
    a4[2][0] = m[3][0]; a4[2][1] = m[3][1]; a4[2][2] = m[3][2];

    return m[0][0]*determinant3x3(a1)
         - m[0][1]*determinant3x3(a2)
         + m[0][2]*determinant3x3(a3)
         - m[0][3]*determinant3x3(a4);
}
