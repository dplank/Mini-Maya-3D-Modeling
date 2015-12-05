#include "sceneGraph.h"
#include <assert.h>

sceneGraph::sceneGraph()
{
    head = new sceneNode();
}

sceneGraph::~sceneGraph()
{
    delete head;
}

void sceneGraph::start(GLWidget277 &glWid, ShaderProgram &shaderPro) {
    // start traverse function of root node
    if(head!=nullptr){
        head->traverse(mat4::identity(),glWid, shaderPro);
        head->setText(0,"root"); //for HW3
    }
}

void sceneGraph::addNode(int level, int childNo, QString name,
                         float scaleX, float scaleY, float scaleZ,
                         float rotX, float rotY, float rotZ,
                         float transX, float transY, float transZ,
                         vec4 pivot) {


    sceneNode *toAdd;
    int locChildren=0; // creating local Children variable here as globle value at recursion

    toAdd = head->find(level, childNo, 0, &locChildren); // procedure retrun node of required level and childNo

    toAdd->addChild(name,
                    scaleX,scaleY,scaleZ,
                    transX,transY,transZ,
                    rotX,rotY,rotZ,
                    pivot);


}

void sceneGraph::addGeometry(int level, int childNo, ShaderProgram::Drawable *geom, sceneNode::geomType t, vec4 inColor)  {

    sceneNode *toAdd;
    int locChildren=0;
    toAdd = head->find(level, childNo, 0, &locChildren);
    assert(toAdd!=nullptr); // if toAdd is nullptr
    toAdd->addGeometry(geom,t, inColor);

    geometryNodes.push_back(toAdd);

}
