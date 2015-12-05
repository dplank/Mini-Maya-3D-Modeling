#ifndef OCTREE_H
#define OCTREE_H

//**Pre procesing step
//-need to create bounding box for all geometry
//-need to create root or initial octree
//-then need recursively add it's children (4 at every depth's child) untill we get 1 or 0 non-shared geometry

//**During picking
//check is initial bounding box hit's ray,if yes then sort it's 4 child in increasing order of t(distance from ray
//origin) then recursively call this function again in sorted oreder for all boxes
//if we reach to leaf where it has no child, now check for all geometry it has using algo similar to testIntersection
//in "mygl.cpp"
//if find geometry then return true
//otherwise return false


// ** data types ** //
//1. contain min and max at all axis for box it has
//2. vector of pointer contain all geometry that fits within this box
//3. 4 of it child octree nodes
//4. complete geometries, contain no. of geometry that is contain completely within it

// ** methods ** //
//1. constructor take scene graph as argument and calculate first box that covers all geometries bounding boxes
//2. this constructor take min and max values passed as argument and set it to it's minMax values for all axis
//3. start Root just take input completed sceneGraph and initialize all it's contains
     //only for root node
//4. add geometry, takes pointer to sceneNode and add to it's geometry Nodes list
//5. drawOTree, just draw octree as empty boxes

#include<sceneGraph.h>
#include<vector>
#include<glwidget277.h>
#include<shaderprogram.h>
#include"scene/box.h"

class octree
{
public: //Data types
    //1.
    float minMaxX[2], minMaxY[2], minMaxZ[2];
    //2.
    std::vector<sceneNode *> geometryNodes;
    //3. //every time it contain either 8 or 0 number
    std::vector<octree *>children;
    //4.
    int completeGeom;

public: //Methods
    //1.
    octree();
    //2.
    octree(float minX, float maxX,
           float minY, float maxY,
           float minZ, float maxZ);
    //3.
    void startRoot(sceneGraph *g); //only call for root node
    //4.
    void addGeometry(sceneNode *n);
    //5.
    void drawOTree(GLWidget277 &glWid, ShaderProgram &shaderP, Box &box);

    ~octree();
};

#endif // OCTREE_H
