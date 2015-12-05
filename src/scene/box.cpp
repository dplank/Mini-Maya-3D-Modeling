#include "box.h"
#define IDX_COUNT 24

Box::Box(): bufPos(QOpenGLBuffer::VertexBuffer),
            bufIdx(QOpenGLBuffer::IndexBuffer)
{

}

void Box::create(){
    bufPos.create();
    bufIdx.create();
}

void Box::assign(vec4 min, vec4 max) {
    ///initialize postion of vectricies
    vec4 position[8] = { max, vec4(min[0],max[1],max[2],1), vec4(min[0],min[1],max[2],1), vec4(max[0], min[1], max[2],1), //front face
                         vec4(max[0],max[1],min[2],1), vec4(min[0],max[1],min[2],1), min, vec4(max[0], min[1], min[2],1)};//back face

    static bool display=true;
    if(display){
        for(int i=0; i<8; i++){
            //std::cout<<"position no."<<i<<" is: "<<position[i];
        }
        display=false;
    }
    ///initialize indices
    int idx[IDX_COUNT];
    count=IDX_COUNT;
    //for assigning indicies
    //1. assign for front rectangle
    //2. assign for back rectangle
    //3. connecting 4 line front and back rectangle
    int index=0;
    //1.
    for(int i=0; i<4;i++){
        idx[index] = i;
        idx[index+1] = (i+1)%4;
        index+=2;
    }
    //2.
    for(int i=4; i<8; i++) {
        idx[index] = i;
        idx[index+1] = (i+1==8 ? 4 : i+1) ; //assign 4 instead of 8
        index+=2;
    }

    //3.
    for(int i=0; i<4; i++) {
        idx[index] = i;
        idx[index+1] = i+4;
        index+=2;
    }

    bufPos.create();
    bufPos.bind();
    bufPos.allocate( position, 8*sizeof(vec4));

    bufPos.create();
    bufIdx.bind();
    bufIdx.allocate( idx, count * sizeof(int));
}

void Box::destroy() {
    bufPos.destroy();
    bufIdx.destroy();
}

GLenum Box::drawMode(){
    return GL_LINES;
}

int Box::elemCount(){
    return count;
}

bool Box::bindIdx(){
    return bufIdx.bind();
}

bool Box::bindPos(){
    return bufPos.bind();
}

bool Box::bindNor(){
    return false;
}

bool Box::bindCol(){
    return false;
}

Box::~Box()
{

}

