#include "cylinder.h"
#include<la.h>
#include <iostream>

static const int CYL_IDX_COUNT = 240;
static const int CYL_VERT_COUNT = 80;

Cylinder::Cylinder()
  : bufIdx(QOpenGLBuffer::IndexBuffer),
    bufPos(QOpenGLBuffer::VertexBuffer),
    bufNor(QOpenGLBuffer::VertexBuffer),
    bufCol(QOpenGLBuffer::VertexBuffer) {
}

// These are functions that are only defined in this cpp file. They're used for organizational purposes
// when filling the arrays used to hold the vertex and index data.
void createCylinderVertexPositions(vec4 (&cyl_vert_pos)[CYL_VERT_COUNT]) {
  // Create two rings of vertices
  // We'll be using 20-sided polygons to approximate circles
  // for the endcaps

  // Store top cap verts (IDX 0 - 19)
  for(int i = 0; i < 20; i++) {
    vec4 v = mat4::rotate(i * 18.0f, 0, 1, 0) * vec4(0.5f, 0.5f, 0,1);
    cyl_vert_pos[i] = v;
  }

  // Store bottom cap verts (IDX 20 - 39)
  for(int i = 20; i < 40; i++) {
    vec4 v = mat4::rotate((i-20) * 18.0f, 0, 1, 0) * vec4(0.5f, -0.5f, 0,1);
    cyl_vert_pos[i] = v;
  }

  // Create two more rings of vertices, this time for the barrel faces
  // We could use the same vertex rings as above, but GL only supports one normal per vertex
  // so we have to have two vertices per position in order to have sharp edges between the endcaps
  // and the barrel

  // Store top cap verts (IDX 40 - 59)
  for(int i = 0; i < 20; i++) {
    vec4 v = mat4::rotate(i * 18.0f, 0, 1, 0) * vec4(0.5f, 0.5f, 0,1);
    cyl_vert_pos[i + 40] = v;
  }

  // Store bottom cap verts (IDX 60 - 79)
  for(int i = 20; i < 40; i++) {
    vec4 v = mat4::rotate((i - 20) * 18.0f, 0, 1, 0) * vec4(0.5f, -0.5f, 0, 1);
    cyl_vert_pos[i + 40] = v;
  }
}


void createCylinderVertexNormals(vec4 (&cyl_vert_nor)[CYL_VERT_COUNT]){
  //Store top cap normals (IDX 0 - 19)
  for(int i = 0; i < 20; i++){
    cyl_vert_nor[i] =  vec4(0,1,0,0);
  }
  //Store bottom cap normals (IDX 20 - 39)
  for(int i = 20; i < 40; i++){
    cyl_vert_nor[i] =  vec4(0,-1,0,0);
  }

  //Store top of barrel normals (IDX 40 - 59)
  for(int i = 0; i < 20; i++){
    vec4 v = mat4::rotate(i*18.0f, 0, 1, 0) * vec4(1,0,0,0);
    cyl_vert_nor[i + 40] = v;
  }
  //Store bottom of barrel normals (IDX 60 - 79)
  for(int i = 20; i < 40; i++){
    vec4 v = mat4::rotate((i-20)*18.0f, 0, 1, 0) * vec4(1,0,0,0);
    cyl_vert_nor[i + 40] = v;
  }
}


void createCylinderIndices(GLuint (&cyl_idx)[CYL_IDX_COUNT]){
  //Build indices for the top cap (18 tris, indices 0 - 53, up to vertex 19)
  for(int i = 0; i < 18; i++){
    cyl_idx[i*3] = 0;
    cyl_idx[i*3 + 1] = i+1;
    cyl_idx[i*3 + 2] = i+2;
  }
  //Build indices for the top cap (18 tris, indices 54 - 107, up to vertex 39)
  for(int i = 18; i < 36; i++){
    cyl_idx[i*3] = 20;
    cyl_idx[i*3 + 1] = i+3;
    cyl_idx[i*3 + 2] = i+4;
  }
  //Build indices for the barrel of the cylinder
  for(int i = 0; i < 19; i++){
    cyl_idx[108 + i*6] = i + 40;
    cyl_idx[109 + i*6] = i + 41;
    cyl_idx[110 + i*6] = i + 60;
    cyl_idx[111 + i*6] = i + 41;
    cyl_idx[112 + i*6] = i + 61;
    cyl_idx[113 + i*6] = i + 60;
  }
  //Build the last quad of the barrel, which has looping indices
  cyl_idx[234] = 59;
  cyl_idx[235] = 40;
  cyl_idx[236] = 79;
  cyl_idx[237] = 40;
  cyl_idx[238] = 60;
  cyl_idx[239] = 79;
}

void Cylinder::create()
{
  GLuint cyl_idx[CYL_IDX_COUNT];
  vec4 cyl_vert_pos[CYL_VERT_COUNT];
  vec4 cyl_vert_nor[CYL_VERT_COUNT];

  createCylinderVertexPositions(cyl_vert_pos);
  createCylinderVertexNormals(cyl_vert_nor);
  createCylinderIndices(cyl_idx);

  count = CYL_IDX_COUNT;

  bufIdx.create();
  bufIdx.bind();
  bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufIdx.allocate(cyl_idx, CYL_IDX_COUNT * sizeof(GLuint));

  bufPos.create();
  bufPos.bind();
  bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufPos.allocate(cyl_vert_pos,CYL_VERT_COUNT * sizeof(vec4));

  bufNor.create();
  bufNor.bind();
  bufNor.setUsagePattern(QOpenGLBuffer::StaticDraw);
  bufNor.allocate(cyl_vert_nor, CYL_VERT_COUNT * sizeof(vec4));
}


void Cylinder::destroy()
{
  bufIdx.destroy();
  bufPos.destroy();
  bufNor.destroy();
  bufCol.destroy();
}

GLenum Cylinder::drawMode()
{
  return GL_TRIANGLES;
}

int Cylinder::elemCount()
{
  return count;
}

bool Cylinder::bindIdx()
{
  return bufIdx.bind();
}

bool Cylinder::bindPos()
{
  return bufPos.bind();
}

bool Cylinder::bindNor()
{
  return bufNor.bind();
}

bool Cylinder::bindCol()
{
  return bufCol.bind();
}
