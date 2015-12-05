#ifndef SCENENODE_H
#define SCENENODE_H

#include "linear_algebra/mat4.h"
#include "linear_algebra/vec4.h"
#include <vector>
#include <shaderprogram.h>


#include<QTreeWidgetItem>  //for HW 3


// ** data type ** //
// 0. pointer pointing to parent
// 1. vector of pointer to "graphNode" type
// 2. A pointer points to geometry to render
// 3. three array data type contain values for generation translation, rotation and scale matrix
// (later) [we reomove this as we can build on traversing and not use on other place] One Identity
//matrix which post multiply it's parent matrix then multiply it ( translation * rotation * scale ) matrix
// 4. color of geometry it contain
// 5. 'pivot' set the pivot of rotation and scale for this node
// 6. 'geomType' is enum type tells what type of geometry it is
//for HW4
// 7. minMaxX, minMaxY, minMaxZ, contain axis aligned boundiing box for nodes contain geometry other wise it is 0;s


//***CAUTION***//
//Not create new geometry object for any node, becuse whole purpose of scene graph is nodes pointing to same
//geometry


// ** methods ** //
// 0. default constructor is initialize transformation which can't affect it's geometry position and
//    another constructor just initialize values with passed parameter.
// 1. add child "parameter" is (scaleX, scaleY, scaleZ, transX, transY, transZ, roationAngle, rotX, rotY, rotZ)
//    now it just creat new node with above values and push back to it's vector of children ALSO it set parent of
//    newly created child with this pointer
// 2. traverse method is recursion based use to traverse through all of it's chlidren with passing current
//    transformations and draw geometry where they have
// 3. addGeometry just add new geometry, and these geometry is not newely created but it's pointing to a single centralize
//    geometry, also it contain color for that node
// 4. find function returns pointer to node which has "level" level no. and "childNo" as require child of that level
//    here level start's with 0, and childNo for each level start from 1.
// 5. set parent node
// 6. get parent node
// 7. get resultant matrix for this node
// End. destructor delete all it's children

//Extra learnig:- givind uninitialized pointer as argument is waist

class sceneNode : public QTreeWidgetItem // for HW 3
{
private:
    //0.//
    sceneNode* parent;

    //1.//
public:
    std::vector <sceneNode*> childNode;

    //2.//
private:
    ShaderProgram::Drawable *geometry;

    //3.//
public:
    float scale[3];
    float translate[3];
    float rotation[3];
    //4.//
    vec4 color; //In range of 0-1

    //5.//
    vec4 pivot;

    //6.//
    enum geomType {NONE, SPHERE, CYLINDER, CUBE};
    geomType type;

    //7.// HW4 for bounding box, calculated in addGeometry
    float minMaxX[2],minMaxY[2],minMaxZ[2];

public:
    //0.
    sceneNode(); // default constructor intialize transformations with non affecting values.

    sceneNode(float scaleX, float scaleY, float scaleZ, //first scale
              float transX, float transY, float transZ, //second translatoin
              float rotX, float rotY, float rotZ, vec4 inPivot);

    //1.//
    sceneNode *addChild(QString name,
                  float scaleX, float scaleY, float scaleZ, //first scale
                  float transX, float transY, float transZ, //second translatoin
                  float rotX, float rotY, float rotZ, vec4 pivot); //third rotation

    //2.//
    void traverse(mat4 parentMatrix, GLWidget277 &glWid, ShaderProgram &shaderPro);

    //3.//
    void addGeometry(ShaderProgram::Drawable *newGeometry, geomType type, vec4 inColor);

    //4.//
    sceneNode *find(int level,int childNo,int locLevel,int *locChildren);//using ptr argument to enable recursion
                                                                                         //evenly only retrning is sufficient.
    //5.//
    void setParent(sceneNode* inParent);

    //6.//
    sceneNode* getParent();

    //7.//
    mat4 getResultaint();
    //end.//
    ~sceneNode();
};

#endif // SCENENODE_H
