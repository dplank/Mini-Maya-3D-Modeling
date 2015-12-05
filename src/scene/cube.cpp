#include "cube.h"

const int POS_COUNT = 24; //6 * 4 verticies in cube
const int IDX_COUNT = 36; //6 * 6 as need 6 indicies per quad

//initialize all buffer objects
Cube::Cube(): bufIdx(QOpenGLBuffer::IndexBuffer),
              bufPos(QOpenGLBuffer::VertexBuffer),
              bufCol(QOpenGLBuffer::VertexBuffer),
              bufNor(QOpenGLBuffer::VertexBuffer)

{

}

//Impliment create() which create array of data, then create
//Opengl buffers and allocate it with vertex, idex, color, normal

void createCubePosition (vec4 (&pos)[POS_COUNT]){
    //As GL support normal per vertex so we have to create per
    // face separatly

    // top face z=1
    pos[0]=vec4(-0.5, 0.5, 0.5, 1.0); // far left
    pos[1]=vec4(0.5, 0.5, 0.5, 1.0); // far right
    pos[2]=vec4(-0.5, -0.5, 0.5, 1.0); // near left
    pos[3]=vec4(0.5, -0.5, 0.5, 1.0); // near right

    // bottom face z=-1
    pos[4]=vec4(-0.5, 0.5, -0.5, 1.0); // far left
    pos[5]=vec4(0.5, 0.5, -0.5, 1.0); // far right
    pos[6]=vec4(-0.5, -0.5, -0.5, 1.0); // near left
    pos[7]=vec4(0.5, -0.5, -0.5, 1.0); // near right

    // right face x = 1
    pos[8]=vec4(0.5, -0.5, 0.5, 1.0); // up near
    pos[9]=vec4(0.5, 0.5, 0.5, 1.0); // up far
    pos[10]=vec4(0.5, -0.5, -0.5, 1.0); // down near
    pos[11]=vec4(0.5, 0.5, -0.5, 1.0); // down far

    // left face x = -1
    pos[12]=vec4(-0.5, -0.5, 0.5, 1.0); // up near
    pos[13]=vec4(-0.5, 0.5, 0.5, 1.0); // up far
    pos[14]=vec4(-0.5, -0.5, -0.5, 1.0); // down near
    pos[15]=vec4(-0.5, 0.5, -0.5, 1.0); // down far

    // near face y = -1
    pos[16]=vec4(-0.5, -0.5, 0.5, 1.0); // up left
    pos[17]=vec4(0.5, -0.5, 0.5, 1.0); // up right
    pos[18]=vec4(-0.5, -0.5, -0.5, 1.0); // down left
    pos[19]=vec4(0.5, -0.5, -0.5, 1.0); // down right

    // far face y = 1
    pos[20]=vec4(-0.5, 0.5, 0.5, 1.0); // up left
    pos[21]=vec4(0.5, 0.5, 0.5, 1.0); // up right
    pos[22]=vec4(-0.5, 0.5, -0.5, 1.0); // down left
    pos[23]=vec4(0.5, 0.5, -0.5, 1.0); // down right

}

void createCubeNormal (vec4 (&nor)[POS_COUNT]){
    //top face
    for(int i=0; i<4; i++) {
        nor[i]=vec4(0.0, 0.0, 1.0, 0.0);
    }

    //bottom face
    for(int i=0; i<4; i++) {
        nor[4+i]=vec4(0.0, 0.0, -1.0, 0.0);
    }

    //right face
    for(int i=0; i<4; i++) {
        nor[8+i] = vec4(1.0, 0.0, 0.0, 0.0);
    }

    //left face
    for(int i=0; i<4; i++) {
        nor[12+i] = vec4(-1.0, 0.0, 0.0, 0.0);
    }

    //near face
    for(int i=0; i<4; i++) {
        nor[16+i] = vec4(0.0, -1.0, 0.0, 0.0);
    }

    //far face
    for(int i=0; i<4; i++) {
        nor[20+i] = vec4(0.0, 1.0, 0.0, 0.0);
    }
}

void createCubeIndicies (GLuint (&idx)[IDX_COUNT]){

    int index=0;

    //Iteration per face
    for(int j=0; j<6; j++) {
        int i = j*4;
        idx[index]     = i;
        idx[index + 1] = i+1;
        idx[index + 2] = i+2;

        idx[index + 3] = i+1;
        idx[index + 4] = i+2;
        idx[index + 5] = i+3;
        index += 6;
    }
}


void Cube::create(){
    count = IDX_COUNT;
    vec4 position[POS_COUNT];
    vec4 normal[POS_COUNT];
    GLuint indicies[IDX_COUNT];

    // assigning position, norma and it's indices
    createCubePosition(position);
    createCubeNormal (normal);
    createCubeIndicies(indicies);

    //Creating openGL buffers by process of:-
        //1.create
        //2.bind as current opengl context
        //3.set draw method like static draw
        //4.allocate data in buffer

    bufIdx.create();
    bufIdx.bind();
    bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufIdx.allocate(indicies, IDX_COUNT * sizeof(GLuint));

    bufPos.create();
    bufPos.bind();
    bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufPos.allocate(position, POS_COUNT * sizeof(vec4));

    bufNor.create();
    bufNor.bind();
    bufNor.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufNor.allocate(normal, POS_COUNT * sizeof(vec4));

}

void Cube::destroy() {
    // this distroy all buffer objects, which include
    // storage used in openGL server. and all references
    // to buffer will become invalid.

    bufIdx.destroy();
    bufPos.destroy();
    bufCol.destroy();
    bufNor.destroy();
}

GLenum Cube::drawMode() {
    return GL_TRIANGLES;
}

int Cube::elemCount() {
    return count;
}

bool Cube::bindIdx() {
    return bufIdx.bind();
}

bool Cube::bindPos() {
    return bufPos.bind();
}

bool Cube::bindNor() {
    return bufNor.bind();
}

bool Cube::bindCol () {
    return bufCol.bind();
}

