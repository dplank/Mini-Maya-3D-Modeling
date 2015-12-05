#ifndef Ray_H
#define Ray_H

#include <shaderprogram.h>

class Ray : public ShaderProgram::Drawable
{
private:
    int count;
    QOpenGLBuffer bufIdx;
    QOpenGLBuffer bufPos;

public:
    Ray();
    ~Ray();

    void create();
    void destroy();
    void setRay(vec4, vec4);

    //virtual function that compulsory to have in

    GLenum drawMode();
    int elemCount();

    bool bindIdx();
    bool bindPos();
    bool bindNor();
    bool bindCol();
};

#endif // Ray_H
