#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H


//  Concept of level index and child number indexing

                //         //
                // head   //
//                  |
//                  v
//               rootNode       level: 0  /**/It's parent is nullptr, use ful for getting resultant
//              (childNo 1)               /**/matrix for any child as boundry condition
//                /   \
//               /     \
//          child_1    child_2   level: 1
//       (childNo 1)  (childNo 2)



#include "sceneNode.h"
#include <vector>

// ** data type ** //
// 1. Scene Graph contain one header pointing to root of graph
// 2. vector of all nodes contain geometry // for HW 4

// ** methods ** //
//0. default constructor just create root node and initialize
//1. start method start traversing which use it's head pointer to call root node's traverse Method by passing 'Identity matrix'
//    and current glwidget object to use core opengl functions and shader object to use it to draw
//2. add node method add's child at given level and given it's child no. also user provide paramete of transformation
//   (scale, trans, rotate) which that node contain. along with geomery
//3. add geomery method add's geometry at given level and given child no.


// Contain destructor which delete it's root and every node delete it's child nodes



class sceneGraph
{
public:
    sceneNode *head ;
    std::vector <sceneNode*> geometryNodes; // for HW 4

public:
    //0.
    sceneGraph();
    ~sceneGraph();
    //1.
    void start(GLWidget277 &glWid, ShaderProgram &shaderPro);
    //2.
    void addNode(int level, int childNo, QString name,
                 float scaleX, float scaleY, float scaleZ,
                 float rotX, float rotY, float rotZ,
                 float transX, float transY, float transZ,
                 vec4 pivot = vec4(0,0,0,1));
    //3.
    void addGeometry (int level, int childNo, ShaderProgram::Drawable *geom,sceneNode::geomType t, vec4 inColor);

};

#endif // SCENEGRAPH_H
