#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/cube.h>
#include <scene/ray.h> //for HW4
#include <scene/box.h> //for HW4

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "sceneGraph.h" // for HW 2
#include<camera.h> //for HW 3
#include "octree.h" //for HW 4

class MyGL
: public GLWidget277 {

    Q_OBJECT

 private:  //D:Members
  QOpenGLVertexArrayObject vao;

  Cylinder geom_cylinder;//The instance of a unit cylinder we can use to render any cylinder
  Sphere geom_sphere;//The instance of a unit sphere we can use to render any sphere
  Cube geom_cube;//TODO: Add a cube instance
  Ray geom_ray; //for HW4 to draw a ray
  Box geom_box;


  ShaderProgram prog_lambert;
  ShaderProgram prog_wire;

  sceneGraph mainGraph; //for HW2

 private:
  camera c; // for HW3
  bool right;//for mouse interaction
  bool left;//for mouse interaction
  bool middel;//for mouse interaction

  int oldX,oldY;  //for mouse interaction
  bool altPressed; //HW4 switch from selection to view mode

  vec4 rayP; //HW4 current ray position
  vec4 rayD; //HW4 current ray direction

  octree mainOctree; //HW4 root octree contain all geometry and biggest cube
  int testPerformed; //HW4 for performance, show how many times geometry, ray test runs
  bool octreeVisible; //HW4 turn on/off by signal come from octreeBox

 public: //D:Methods
  explicit MyGL(QWidget *parent = 0);
  ~MyGL();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  sceneNode* testIntersection(vec4 Point, vec4 Direction, std::vector<sceneNode *> &geometries
                              ,/*next para. for rayTracer*/float *rayTraT=nullptr, mat4 *rayTraM=nullptr, bool needRayTraM=false); //for HW4
  void buildOctree(); //for HW4 build complete octree on initializeGL
  sceneNode * octreeIntersectionTest(vec4 point, vec4 direction, octree& oTree); //for HW4 start traversing for given ray on mainOctree
  void generateRay(int x, int y); //for HW4 RayTracer


protected:

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e); //HW4 to set mode from select to view
  void mouseMoveEvent(QMouseEvent *e); // for HW3
  void mousePressEvent(QMouseEvent *e); // for HW3

  void createCharactor();

  void proceduralGraph();

  //D: Signal and Slot

  signals:  // for HW3//D: sending root of scene graph to Tree Widget
  void sig_sendTopItem(QTreeWidgetItem *item);

  //HW4 signal that was selected from ray picking
  void sig_sendSelectedItem(QTreeWidgetItem *item);


public slots: //for HW 3, receive signal from mainWindow to add child and
              //assign required geometry
  void slot_addChild(sceneNode* node,sceneNode::geomType geometry, QString name);

  void slot_showOctree(bool); //HW4

  //for HW4, receive signal from mainWindow to eliminate sceneNode from vector list of node
  //contain geometry in sceneGraph data structure
  void slot_removeGeomNodes(sceneNode*);

  void slot_RenderRays(); //HW4: Start ray tracer, connect with 'start ray tracer' button
};


#endif // MYGL_H
