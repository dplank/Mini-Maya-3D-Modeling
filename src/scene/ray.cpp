#include "ray.h"

#define COUNT 2

Ray::Ray(): bufIdx(QOpenGLBuffer::IndexBuffer),
            bufPos(QOpenGLBuffer::VertexBuffer)
{


}

//impliment create funnction that create data first,
//initialize openGL buffer and bind data to appropriate buffers

void Ray::create(){
    std::cout<<"is created ray pos: "<<bufPos.create()<<std::endl;
    std::cout<<"is created ray index: "<<bufIdx.create()<<std::endl;
}

void Ray::setRay(vec4 point, vec4 direction) {

    ///create data which need to send to indicies
    count = COUNT;

    //1. point data
    vec4 point2 = point + 100*direction;
    vec4 points[COUNT] = {point, point2};

    //2. Index data
    GLuint index[COUNT] = {0,1};


    ///create buffers on GPU


    //1. point buffer
    bufPos.bind();
    bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufPos.allocate(points, COUNT*sizeof(vec4));

    //2. create index

    bufIdx.bind();
    bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufIdx.allocate(index, COUNT*sizeof(GLuint));
}

void Ray::destroy() {
    bufIdx.destroy();
    bufPos.destroy();
}

GLenum Ray::drawMode() {
    return GL_LINES;
}

int Ray::elemCount() {
    return count;
}

bool Ray::bindIdx() {
    return bufIdx.bind();
}

bool Ray::bindPos() {
    return bufPos.bind();
}

bool Ray::bindNor() {
    return false;
}

bool Ray::bindCol() {
    return false;
}


Ray::~Ray()
{

}

