#include "octree.h"

octree::octree()
{
    completeGeom = 0;
}


octree::octree(float minX, float maxX,
               float minY, float maxY,
               float minZ, float maxZ){
    completeGeom = 0;

    minMaxX[0]=minX; minMaxX[1]=maxX;
    minMaxY[0]=minY; minMaxY[1]=maxY;
    minMaxZ[0]=minZ; minMaxZ[1]=maxZ;
}


void octree::startRoot(sceneGraph *g){

    //initialize with first node in vector of geometryNodes in graph
    sceneNode *current = g->geometryNodes[0];
    geometryNodes.push_back(current);//store this node in geometryNodes
    completeGeom = g->geometryNodes.size(); //it has all geometry completly within it

    minMaxX[0]=current->minMaxX[0];
    minMaxX[1]=current->minMaxX[1];

    minMaxY[0]=current->minMaxY[0];
    minMaxY[1]=current->minMaxY[1];

    minMaxZ[0]=current->minMaxZ[0];
    minMaxZ[1]=current->minMaxZ[1];

    //iterate through all node contains geometry and checking for min and max for all axises
    for(int i=1; i< g->geometryNodes.size(); i++){

        current = g->geometryNodes[i];
        geometryNodes.push_back(current);//store this node in geometryNode

        if( minMaxX[0] > current->minMaxX[0] ) //for minX
            minMaxX[0] = current->minMaxX[0];

        if( minMaxX[1] < current->minMaxX[1] ) //for maxX
            minMaxX[1] = current->minMaxX[1];

        if( minMaxY[0] > current->minMaxY[0] ) //for minY
            minMaxY[0] = current->minMaxY[0];

        if( minMaxY[1] < current->minMaxY[1] ) //for maxY
            minMaxY[1] = current->minMaxY[1];

        if( minMaxZ[0] > current->minMaxZ[0] ) //for minZ
            minMaxZ[0] = current->minMaxZ[0];

        if( minMaxZ[1] < current->minMaxZ[1] ) //for maxZ
            minMaxZ[1] = current->minMaxZ[1];

    }

    std::cout<<"minimum: "<<vec4(minMaxX[0],minMaxY[0],minMaxZ[0],1);
    std::cout<<"maximul: "<<vec4(minMaxX[1],minMaxY[1],minMaxZ[1],1);
}

void octree::addGeometry(sceneNode *n){
    geometryNodes.push_back(n);
}

void octree::drawOTree(GLWidget277 &glWid, ShaderProgram &shaderP, Box &box){
    vec4 min(minMaxX[0],minMaxY[0], minMaxZ[0], 1);
    vec4 max(minMaxX[1], minMaxY[1], minMaxZ[1], 1);

//    static int count=0;
//    if(count<8){
//        std::cout<<"min: "<<min;
//        std::cout<<"max: "<<max;
//        count++;
//    }

    box.assign(min, max);

    mat4 model(1);

    shaderP.prog.bind();
    shaderP.setModelMatrix(model);
    shaderP.draw(glWid, box);

    octree *current;
    for(int i=0; i< children.size(); i++){
        current = children[i];
        current->drawOTree(glWid, shaderP, box);
    }
}

octree::~octree()
{

}
