#ifndef LA
#define LA

#include <QMatrix4x4>
#include<QVector4D>
#include "linear_algebra/mat4.h"


/// 277 linear algebra namespace
namespace la {
    QMatrix4x4 to_qmat(const mat4 &m);
    QVector4D to_qvec(const vec4 &v);
    mat4 inverse(mat4 m);
    float determinant4x4(const mat4& m);
    float determinant3x3(const float(&m)[3][3]);
    float determinant2x2(const float(&m)[2][2]);
}


#endif // LA
