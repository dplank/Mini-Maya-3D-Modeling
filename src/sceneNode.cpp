
#include "sceneNode.h"

sceneNode::sceneNode() {
    //initialize geometry and parent
    geometry = nullptr;
    parent = nullptr;
    //initialize boinding box, this will change in addChild method
    for(int i=0;i<2;i++){
        minMaxX[i]=0;
        minMaxY[i]=0;
        minMaxZ[i]=0;
    }


    for(int i=0; i<3; i++){
        scale[i]=1;
        translate[i]=0;
        rotation[i]=0;
    }
    //resultMatrix = mat4::identity();
    type=sceneNode::NONE; // default geometry is none //HW3
}

sceneNode::sceneNode(float scaleX, float scaleY, float scaleZ,
                     float transX, float transY, float transZ,
                     float rotX, float rotY, float rotZ,
                     vec4 inPivot)
{
    //initialize geometry and parent
    geometry = nullptr;
    parent = nullptr;
    //initialize boinding box, this will change in addChild method
    for(int i=0;i<2;i++){
        minMaxX[i]=0;
        minMaxY[i]=0;
        minMaxZ[i]=0;
    }

    scale[0] = scaleX; scale[1] = scaleY; scale[2] = scaleZ;
    translate[0] = transX; translate[1] = transY; translate[2] = transZ;
    rotation[0] = rotX; rotation[1] = rotY; rotation[2] = rotZ;

    pivot = inPivot;

    type=sceneNode::NONE; // default geometry is none //HW3
}

sceneNode* sceneNode::addChild(QString name,
                         float scaleX, float scaleY, float scaleZ,
                         float transX, float transY, float transZ,
                         float rotX, float rotY, float rotZ,
                         vec4 pivot) {

    sceneNode *newChild = new sceneNode(scaleX, scaleY, scaleZ,
                                       transX, transY, transZ,
                                       rotX, rotY, rotZ,
                                       pivot);
    QTreeWidgetItem::addChild(newChild);

    newChild->setText(0,name);

    childNode.push_back(newChild); //push back newly created child
    newChild->setParent(this); //set parent of newly created child

    return newChild;
}

void sceneNode::traverse(mat4 parentMatrix, GLWidget277 &glWid, ShaderProgram &shaderPro) {
    // 1.copy the passed matrix to result matrix
    // 2.post multiply local transformation data
    // 3.iterate over all it's children by calling their traverse functions
    // 4.draw it's own geometry

    //std::cout<<color<<std::endl;  //

    //1.
    mat4 resultMatrix = parentMatrix;
    //2.
    resultMatrix = resultMatrix * mat4::translate(translate[0],translate[1],translate[2])

                                * mat4::translate(pivot[0], pivot[1], pivot[2]) // moving pivot point back to original
                                * mat4::rotate(rotation[0], 1, 0, 0) // x-axis
                                * mat4::rotate(rotation[1], 0, 1, 0) // y-axis
                                * mat4::rotate(rotation[2], 0, 0, 1) // z-axis
                                * mat4::scale(scale[0],scale[1],scale[2])
                                * mat4::translate(-pivot[0], -pivot[1], -pivot[2]); //moving pivot point to origin
    //3.
    for(unsigned int i=0; i<childNode.size(); i++) {
        childNode[i]->traverse(resultMatrix, glWid, shaderPro);
    }

    //4.
    //std::cout<<"in traversal"<<std::endl; //
    if(geometry != nullptr){
        //std::cout<<"called geometry"<<std::endl;  //
        mat4 model = transpose(resultMatrix);
        shaderPro.setModelMatrix(model);
        geometry->setColor(color);
        shaderPro.draw(glWid,*geometry);
    }

}

//this contain calculation for bounding box
void sceneNode::addGeometry(ShaderProgram::Drawable *newGeometry,sceneNode::geomType t, vec4 inColor){

    geometry = newGeometry;
    color = inColor;
    type=t;


    ///now calculating axis aligned bounding box for this node

    //first calculate resultaint transformatoin matrix
    mat4 resultMat(1);
    sceneNode *currentNode=this;
    while(currentNode!=nullptr){
        resultMat = currentNode->getResultaint() * resultMat;
        currentNode = currentNode->getParent();
    }

    //then use this matrix to transform initial box that cover this geometry like 1x1x1 box
    vec4 initBox[8] = {vec4(0.5,0.5,0.5,1), vec4(-0.5,0.5,0.5,1), vec4(-0.5,-0.5,0.5,1), vec4(0.5,-0.5,0.5,1), //front face
                       vec4(0.5,0.5,-0.5,1), vec4(-0.5,0.5,-0.5,1), vec4(-0.5,-0.5,-0.5,1), vec4(0.5,-0.5,-0.5,1)}; //back face
    for(int i=0; i<8; i++){
        initBox[i] = resultMat * initBox[i];
    }

    //now calculate min and max on each X,Y,Z axis of above transformed box's 8 points and assign them to as resultaint
    //bounding box
    //initialize with first point
    minMaxX[0]=minMaxX[1]=initBox[0][0];
    minMaxY[0]=minMaxY[1]=initBox[0][1];
    minMaxZ[0]=minMaxZ[1]=initBox[0][2];

    for(int i=1; i<8; i++){ //loop through all verticies of transformed box
        if(initBox[i][0]<minMaxX[0]) //for minX
            minMaxX[0]=initBox[i][0];

        if(initBox[i][0]>minMaxX[1]) //for maxX
            minMaxX[1]=initBox[i][0];

        if(initBox[i][1]<minMaxY[0]) //for minY
            minMaxY[0]=initBox[i][1];

        if(initBox[i][1]>minMaxY[1]) //for maxY
            minMaxY[1]=initBox[i][1];

        if(initBox[i][2]<minMaxZ[0]) //for minZ
            minMaxZ[0]=initBox[i][2];

        if(initBox[i][2]>minMaxZ[1]) //for maxZ
            minMaxZ[1]=initBox[i][2];
    }
}

sceneNode *sceneNode::find(int level, int childNo,int locLevel, int *locChildren) {
    //0. if at initial stage level==locLevel then we return pointer which head of sceneGraph points to that is this
    //   pointer
    //1. check whether locLevel is above requred level, if yes then add it's children to locChild and check whether
    //   it exceed or equal requred childNo, if yes then find child index and return it's pointer
    //2. otherwise iterate through all children and call their find function with +1 parameter of locLevel, now check
    //   whether whether it's child's find function return nullptr or nor, if not then just return that ptr.

    //0.
    if(level==locLevel)
        return this;

    //1.
    sceneNode *ptr=nullptr;
    if( locLevel == level-1) {
        *locChildren += childNode.size();

        if((*locChildren) >= childNo) {
            int child = childNo - (*locChildren - childNode.size());
            ptr = childNode[child-1];
            return ptr;
        }

    //2.
    } else {
        for(unsigned int i=0 ; i < childNode.size(); i++){
            ptr = (childNode[i])->find(level, childNo, locLevel+1, locChildren); // recursion here
            if(ptr!=nullptr)
                return ptr;
        }
    }

    return ptr; //it is always nullptr

}

void sceneNode::setParent(sceneNode* inParent){
    parent = inParent;
}

sceneNode *sceneNode::getParent(){
    return parent;
}

sceneNode::~sceneNode() {
    //std::cout<<"Scene node destructor called"<<std::endl;
    for(unsigned int i=0; i<childNode.size(); i++) {
        delete childNode[i];
    }
}

mat4 sceneNode::getResultaint() {
    mat4 resultMatrix =     mat4::translate(translate[0],translate[1],translate[2])

                            * mat4::translate(pivot[0], pivot[1], pivot[2]) // moving pivot point back to original
                            * mat4::rotate(rotation[0], 1, 0, 0) // x-axis
                            * mat4::rotate(rotation[1], 0, 1, 0) // y-axis
                            * mat4::rotate(rotation[2], 0, 0, 1) // z-axis
                            * mat4::scale(scale[0],scale[1],scale[2])
                            * mat4::translate(-pivot[0], -pivot[1], -pivot[2]); //moving pivot point to origin
    return resultMatrix;
}


