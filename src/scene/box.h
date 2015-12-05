#ifndef BOX_H
#define BOX_H

#include "shaderprogram.h"
#include <QOpenGLBuffer>

class Box : public ShaderProgram::Drawable
{
private:
    QOpenGLBuffer bufPos;
    QOpenGLBuffer bufIdx;
    int count; //total no of indecies

public:
    Box();
    void create();
    void assign(vec4 min, vec4 max); //creat and fill buffers of position and index
    void destroy();

    //vertual functions form Drawable that need to be implement
    GLenum drawMode();
    int elemCount();
    bool bindIdx();
    bool bindPos();
    bool bindNor();
    bool bindCol();

    ~Box();
};

#endif // BOX_H
