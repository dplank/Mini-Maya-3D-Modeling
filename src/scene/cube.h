#ifndef CUBE_H
#define CUBE_H

#include<shaderprogram.h> // to inherit drawing related functions
#include<QOpenGLBuffer>

#include<linear_algebra/vec4.h>

#include <QOpenGLContext>
#include <QOpenGLShaderProgram>

class Cube: public ShaderProgram::Drawable {
private:
    int count;
    QOpenGLBuffer bufIdx;
    QOpenGLBuffer bufPos;
    QOpenGLBuffer bufCol;
    QOpenGLBuffer bufNor;


public:
    Cube();

    void create();
    void destroy();

    virtual GLenum drawMode();
    virtual int elemCount();
    virtual bool bindIdx();
    virtual bool bindPos();
    virtual bool bindNor();
    virtual bool bindCol();

};

#endif // CUBE_H
