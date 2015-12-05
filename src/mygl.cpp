#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <stdlib.h> //for random number generator

#include<bmp/EasyBMP.h>

using namespace std;


MyGL::MyGL(QWidget *parent)
  : GLWidget277(parent) {

    altPressed = false; //by default is select mode
    octreeVisible = false; //HW4 by defult octree box not visible
}

MyGL::~MyGL() {
  makeCurrent();

  vao.destroy();
  geom_cylinder.destroy();
  geom_sphere.destroy();
  geom_cube.destroy();
  geom_ray.destroy();
  geom_box.destroy();
}


//character second try for first try look this in HW3
void MyGL::createCharactor() {
    //MAIN BODY//
    //'main body' at 0,1
    mainGraph.addNode(0,1,"main body",
                      1,1,1,
                      0,0,0,
                      0,0,0);

    //CHEST//
    //'chest' at 1,1 with cube
    mainGraph.addNode(1,1,"chest",
                      2,4,1,
                      0,0,0,
                      0,0,0);
    mainGraph.addGeometry(2,1,&geom_cube,sceneNode::CUBE, vec4(0,0,1,1));


    //HEAD//
    //'head' at 1,1 with sphere
    mainGraph.addNode(1,1,"head",
                      2,2,2,
                      0,0,0,
                      0,2.5,0,
                      vec4(0,-0.5,0,1));
    mainGraph.addGeometry(2,2,&geom_sphere ,sceneNode::SPHERE, vec4(1,0,0,1));


    //LEFT LEG//
    //'left leg' at 1,1
    mainGraph.addNode(1,1,"left leg",
                      1,1.5,1,
                      0,0,-90,
                      -0.5,-2,0);

        //'left upper leg' at 2,3 with cylinder
        mainGraph.addNode(2,3,"upper leg",
                          1,1,1,
                          0,0,0,
                          0,-0.5,0);
        mainGraph.addGeometry(3,1, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,0,1));
        //'left lower leg' at 2,3 with cylinder
        mainGraph.addNode(2,3,"lower leg",
                          1,1,1,
                          0,0,0,
                          0,-1.5,0,
                          vec4(0,0.5,0,1));
        mainGraph.addGeometry(3,2, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,0,1));

    //RIGHT LEG//
    //'right leg' at 1,1
        mainGraph.addNode(1,1,"right leg",
                          1,1,1,
                          -90,0,0,
                          0.5,-2,0);

        //'right upper leg' at 2,4 with cylinder
        mainGraph.addNode(2,4,"upper leg",
                          1,1,1,
                          0,0,0,
                          0,-0.5,0);
        mainGraph.addGeometry(3,3, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,0,1));
        //'right lower leg' at 2,4 with cylinder
        mainGraph.addNode(2,4,"lower leg",
                          1,1,1,
                          0,0,0,
                          0,-1.5,0,
                          vec4(0,0.5,0,1));
        mainGraph.addGeometry(3,4, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,0,1));

    //LEFT HAND//
    //'left hand' at 1,1
    mainGraph.addNode(1,1,"left hand",
                      1,1,1,
                      0,45,0,
                      -1,0.5,0);
        //'left lower hand control' at 2,5 with cylinder
        mainGraph.addNode(2,5,"lower hand control",
                          1,1,1,
                          0,0,0,
                          -1,0,0);
            //'left lower hand' at 3,5
            mainGraph.addNode(3,5,"lower hand",
                              1,1,1,
                              0,0,90,
                              -0.5,0,0);
            mainGraph.addGeometry(4,1, &geom_cylinder ,sceneNode::CYLINDER, vec4(1,0,1,1));
        //'left upper hand' at 2,5 with cylinder
        mainGraph.addNode(2,5,"upper hand",
                           1,1,1,
                           0,0,90,
                           -0.5,0,0);
        mainGraph.addGeometry(3,6, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,1,1));

    //RIGHT HAND//
    //'right hand' at 1,1
        mainGraph.addNode(1,1,"right hand",
                          1,1,1,
                          0,0,0,
                          1,0.5,0);
        //'right lower hand control' at 2,6 with cylinder
        mainGraph.addNode(2,6,"lower hand control",
                          1,1,1,
                          0,0,0,
                          1,0,0);
            //'right lower hand' at 3,7
            mainGraph.addNode(3,7,"lower hand",
                              1,1,1,
                              0,0,90,
                              0.5,0,0);
            mainGraph.addGeometry(4,2, &geom_cylinder ,sceneNode::CYLINDER, vec4(1,0,1,1));

            //octree test
            mainGraph.addNode(4,2,"sample",
                              1,1,1,
                              0,0,0,
                              2,0.5,-0.2);
            mainGraph.addGeometry(5,1, &geom_sphere,sceneNode::SPHERE, vec4(0,1,1,1));
            mainGraph.addNode(4,2,"sample2",
                              1,1,1,
                              0,0,0,
                              2,1,-0.2);
            mainGraph.addGeometry(5,2, &geom_sphere,sceneNode::SPHERE, vec4(0,1,1,1));
            mainGraph.addNode(4,2,"sample3",
                              1,1,1,
                              0,0,0,
                              2.5,0.5,-0.2);
            mainGraph.addGeometry(5,3, &geom_sphere,sceneNode::SPHERE, vec4(0,1,1,1));
            mainGraph.addNode(4,2,"sample4",
                              1,1,1,
                              0,0,0,
                              2.5,1,-0.2);
            mainGraph.addGeometry(5,4, &geom_sphere,sceneNode::SPHERE, vec4(0,1,1,1));


        //'right upper hand' at 2,6 with cylinder
            mainGraph.addNode(2,6,"upper hand",
                               1,1,1,
                               0,0,90,
                               0.5,0,0);
            mainGraph.addGeometry(3,8, &geom_cylinder ,sceneNode::CYLINDER, vec4(0,1,1,1));


}

void MyGL::proceduralGraph(){
    for(int i=0; i<10000; i++){
        float x = i*0.09;
        float y = x*sin(3.14 * (x*90)/180);
        float z = x*cos(3.14 * (x*50)/180);
        QString name = "child"+QString::number(i);
        mainGraph.addNode(0,1,name,
                          1,1,1,
                          0,0,0,
                          x,y,z);
        int randN = rand()%3+1;
        switch(randN){
        case 1:
            mainGraph.addGeometry(1,i+1,&geom_sphere,(sceneNode::SPHERE),vec4(0,1,0,1));
            break;
        case 2:
            mainGraph.addGeometry(1,i+1,&geom_cylinder,(sceneNode::CYLINDER), vec4(0,0,1,1));
            break;
        case 3:
            mainGraph.addGeometry(1,i+1,&geom_cube,(sceneNode::CUBE), vec4(0,1,1,1));
            break;
        }
    }
}

void MyGL::initializeGL() {
  std::cout<<"hare krishna beginnig in initialzeGl"<<std::endl;  //

  // Create an OpenGL context
  initializeOpenGLFunctions();

  // Print out some information about the current OpenGL context
  //Darshan:- Comment this out to don't see artifacto on cylinder
  debugContextVersion();

  // Set a few settings/modes in OpenGL rendering
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  // Set the size with which points should be rendered
  glPointSize(5);

  // Set the color with which the screen is filled at the start of each render call.
  glClearColor(0.5, 0.5, 0.5, 1);

  printGLErrorLog();

  // Create a Vertex Attribute Object
  vao.create();
  vao.bind();   // D: bind vao immidiately other wise we have artifacts on cylinder

  //Create the instance of cylinder geometry by filling its VBOs
  geom_cylinder.create();
  geom_cylinder.setColor(vec4(1,0,0,1));

  //Create the instance of sphere geometry by filling its VBOs
  geom_sphere.create();
  geom_sphere.setColor(vec4(0,1,0,1));

  //Here's a good spot to instantiate your cube geometry's VBOs.
  //D: HW 2
  geom_cube.create();

  //HW4 for ray
  geom_ray.create(); //for HW4
  geom_ray.setColor(vec4 (1,0,0,1)); //this is requred and color of ray

  //HW4 for box
  geom_box.create();
  geom_box.setColor(vec4 (1, 0, 0, 1));
  //geom_box.assign(vec4(-8,-8,-8,1), vec4(8,8,8,1));


  // Create and set up the diffuse shader
  prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");

  // Create and set up the wireframe shader
  prog_wire.create(":/glsl/wire.vert.glsl", ":/glsl/wire.frag.glsl");

  // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
  // using multiple VAOs, we can just bind one once.
  vao.bind();

  //D: starting to impliment scene graph here

  createCharactor(); // for HW: 2 //instead using procedurally

  //HW4 need to build procedureally 10,000 geometries
  //proceduralGraph();

  emit sig_sendTopItem(mainGraph.head);//emiting root of sceneGraph

  //HW4 calling buildOctree
  buildOctree();

  std::cout<<"Hari hari end of initialize"<<std::endl;

  system("CLS");

}

void MyGL::resizeGL(int w, int h) {
    //camera width and height for maintaining aspect ration of scene

    c.width=w;
    c.height=h;

    //std::cout<<"called resize gl"<<std::endl;


    //c.zoom = 0.0002;
      mat4 viewproj = c.view();



//Upload the projection matrix
  QMatrix4x4 qviewproj = la::to_qmat(viewproj);

  prog_lambert.prog.bind();
  prog_lambert.prog.setUniformValue(prog_lambert.unifViewProj, qviewproj);

  prog_wire.prog.bind();
  prog_wire.prog.setUniformValue(prog_wire.unifViewProj, qviewproj);

  printGLErrorLog();
}

// This function is called by Qt any time your GL window is supposed to update
// For example, when the function updateGL is called, paintGL is called implicitly.

void MyGL::paintGL() {
  // Clear the screen so that we only see newly drawn images
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //std::cout<<"in paintGL"<<std::endl;  //

  //VVV CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL VVV

  //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
  //Note that we have to transpose the model matrix before passing it to the shader
  //This is because OpenGL exp(mat4::translate(-2,0,0) * mat4::scale(3,3,3));

    //ects column-major matrices, but you've
  //implemented row-major matrices.
  // mat4 model = transpose
//  mat4 model = transpose(mat4::rotate(20,0,0,1) * mat4::scale(1,1.4,1));
//  //Send the geometry's transformation matrix to the shader

//  prog_lambert.setModelMatrix(model);

//  //Set the color with which we want to draw the sphere (green in this case)
//  geom_sphere.setColor(vec4(0,1,0,1));

//  //Draw the example sphere using our lambert shader
//  prog_lambert.draw(*this, geom_cylinder);

  //Here is a good spot to call your scene graph traversal function.
     mainGraph.start(*this,prog_lambert);


     //rendering this ray
     if(rayD!=vec4(0,0,0,0)){
         //std::cout<<"before create"<<std::endl;
         geom_ray.setRay(rayP, rayD);
         //std::cout<<"after create"<<std::endl;

         mat4 model (1);

         prog_wire.prog.bind();
         prog_wire.setModelMatrix(model);

         prog_wire.draw(*this, geom_ray);
        //end of ray
    }

    if(octreeVisible)
         mainOctree.drawOTree(*this, prog_wire, geom_box);

     mat4 viewproj = c.perspective()*c.view();

     viewproj = transpose(viewproj);

    // Upload the projection matrix
    QMatrix4x4 qviewproj = la::to_qmat(viewproj);

    prog_lambert.prog.bind();
    prog_lambert.prog.setUniformValue(prog_lambert.unifViewProj, qviewproj);

    prog_wire.prog.bind();
    prog_wire.prog.setUniformValue(prog_wire.unifViewProj, qviewproj);

}


void MyGL::keyPressEvent(QKeyEvent *e) {
  // http://doc.qt.io/qt-5/qt.html#Key-enum
    this->setFocus();

  if (e->key() == Qt::Key_Escape) {
    QApplication::quit();
  }
  if (e->key() == Qt::Key_Alt){
      altPressed = true;
  }

  //keybord rotation
  if(e->key() == Qt::Key_Left) {
      //std::cout<<"called J"<<std::endl;
      c.theta-=2;
      update();
  }
  if(e->key() == Qt::Key_Right) {
      c.theta+=2;
      update();
  }
  if(e->key() == Qt::Key_Up) {
      c.phi+=2;
      update();
  }
  if(e->key() == Qt::Key_Down) {
      c.phi-=2;
      update();
  }
  if(e->key() == Qt::Key_Q) {
      c.zoom-=0.2;
      update();
  }
  if(e->key() == Qt::Key_A) {
      c.zoom+=0.2;
      update();
  }

}

void MyGL::keyReleaseEvent(QKeyEvent *e) {
    if(e->key()==Qt::Key_Alt){
        altPressed = false;
    }
}

void MyGL::generateRay(int x, int y){
    //generating point on plane parallel to projection of image plane and
    //located at camera reference position. One can locate it anywhere on
    //view vector like on near or far plane

    //1. First convert pixel to NDC
    //2. Generate ray in world coordinate

    //1.

    //get Nx = 2*Px/screenWidth - 1,
    //& Ny = 1 - 2*Py/screenHeight;  // calculate by linear Interpoation
    float Nx = 2.0 * x / c.width - 1;
    float Ny = 1 - 2.0 * y / c.height;

    //2.

    //first calculate view vector, camera right & camera up
    vec4 F = c.ref - c.getPosition();
    vec4 R = c.getRight();
    vec4 U = c.getUp();

    float len = length(F);

    //Horizontal and Vertical vector in plane where we calculating corres.
    //point to NDC
    vec4 V = U * len * tan(c.fovy/2 * PI /180);
    float aspect = c.width/c.height;
    vec4 H = R * aspect * len * tan(c.fovy/2 * PI /180);

    vec4 Pw = c.ref + Nx*H + Ny*V;
    //assigning final position and direction
    rayP = c.getPosition();
    rayD = (Pw-rayP)/length(Pw-rayP);

}

void MyGL::slot_RenderRays(){
    BMP output;
    output.SetSize(c.width, c.height);
    output.SetBitDepth(24);
    cout<<"Ray Tracer Started!"<<endl<<endl;
    cout<<"Total Column: "<<c.width<<endl;
    for(int x = 0; x < c.width; x++){
        cout<<"C: "<<x<<endl;
        for(int y = 0; y < c.height; y++){

            //calculate x,y pixel corresponding ray
            generateRay(x,y); //generate ray of current pixel and put result in rayD and rayP class attribute
            vec4 finalCol;

            ///final geometry, color and point calculation
            //for current ray call ray Intersection test and find final geometry node with
            //minT (in object space) also result matrix of node
            float minT=0;
            mat4 resultMat;
            sceneNode *finalNode = testIntersection(rayP,rayD,mainGraph.geometryNodes,&minT, &resultMat, true);


            if(finalNode == nullptr){ //for non geometry assign background

                finalCol = vec4(0.5,0.5,0.5,1);

            }else{ //for some geometry

                mat4 inverseResultMat = la::inverse(resultMat);
                //first transpose ray in object space then calculate object space point by
                vec4 rayPobj = inverseResultMat * rayP;
                vec4 rayDobj = inverseResultMat * rayD;
                //Pobj = rayPobj + minT*rayDobj;
                vec4 Pobj = rayPobj + minT * rayDobj;

                vec4 light = vec4(5, 5, 3,1);

                ///Shadow test  //***NEED TO FIX SHADOW AND NEGATIVE COMING testT
                //calculate Pworld
                vec4 Pworld = resultMat*Pobj;

                //then create ray from Pworld to light
                vec4 rayToLightP = Pworld;
                vec4 rayToLightD = light - Pworld;
                rayToLightD/=length(rayToLightD); //normalize direction
                rayToLightP = rayToLightP + 0.01 * rayToLightD; //displacing little above surface

                //run intersection of this ray to objects and store result in secondNode
                float testT;
                sceneNode *secondNode = testIntersection(rayToLightP, rayToLightD, mainGraph.geometryNodes,&testT,nullptr,true);

                //check if secondNode != nullptr, finalCol is black
                if(secondNode != nullptr) {
                    finalCol = vec4(0,0,0,1);
                    //cout<<"\nsecondNode: "<<secondNode->text(0).toUtf8().data()<<endl;
                    //cout<<"object T: "<<testT<<endl;
//                    cout<<"\nfinalNode: "<<finalNode->text(0).toUtf8().data()<<endl;

                }
                //else do all below
                else{
                    //cout<<"coming out shadow"<<endl;
                    ///Normal calculation
                    //declare Nobj
                    vec4 Nobj;
                    //if geometry==sphere
                    if(finalNode->type==sceneNode::SPHERE){
                        //Nobj = normalize(objP - (0,0,0))
                        Nobj = Pobj - vec4(0,0,0,1);
                        Nobj = Nobj/length(Nobj);
                    }

                    //if geometry==cylinder
                    if(finalNode->type == sceneNode::CYLINDER){
                        //End caps
                        if(abs(0.5 - abs(Pobj[1])) < 0.001)   //if abs(0.5 - abs(Pobj.y))<0.001
                            if(Pobj[1]>0)   //if P.y > 0 then Nobj is +y Axis
                                Nobj = vec4(0,1,0,0);
                            else    //else Nobj is -y Axis
                                Nobj = vec4(0,-1,0,0);
                        else    //else
                            Nobj = Pobj - vec4(0,Pobj[1],0,1);//Nobj=P-(0,P.y,0)
                    }

                    //if gometry==cube
                    if(finalNode->type == sceneNode::CUBE){
                        if(0.5-Pobj[0] < 0.001) //if (0.5-Pobj.X)<0.001, then Nobj is +x axis
                            Nobj = vec4(1,0,0,0);
                        else if(0.5+Pobj[0] < 0.001)    //else if (0.5+Pobj.X)<0.001, then Nobj is -x axis
                            Nobj = vec4(-1,0,0,0);
                        else if(0.5-Pobj[1] < 0.001)    //else if (0.5-P.Y)<0.001 then Nobj is +y axis
                            Nobj = vec4(0,1,0,0);
                        else if(0.5+Pobj[1] < 0.001)    //else if (0.5+P.Y)<0.001 then Nobj is -y axis
                            Nobj = vec4(0,-1,0,0);
                        else if(0.5-Pobj[2] < 0.001)//else if (0.5-P.z)<0.001 then Nobj is +z axis
                            Nobj = vec4(0,0,1,0);
                        else //else    Nobj is -z axis
                            Nobj - vec4(0,0,-1,0);
                    }
                    //cout<<"result normal: "<<Nobj<<endl;  //
                    //Nworld = inverseTransposeMatrix * Nobj
                    //vec4 Nworld = transpose(inverseResultMat) * Nobj;
                    vec4 Nworld = (transpose(inverseResultMat)) * Nobj;
                    Nworld/=length(Nworld); //**Always remember to normalize

                    //Pworld = resultaintMatrix * Pobj;
                    Pworld = resultMat * Pobj;

                    ///final color for this pixel calculation
                    //light position is (5,5,3)
                    //calculate light direction L = (5, 5, 3) - Pworld;
                    vec4 L = light - Pworld;
                    L = L/length(L);
                    //calculate diffuse factor = clamp(0,1,dot(L,Nworld))
                    float diffFactor = dot(L,Nworld);
                    if(diffFactor < 0)
                        diffFactor=0;

                    //now calculate final color by node.color*(diffuseFactor + ambient) //ambient=0.2
                    finalCol = finalNode->color * (diffFactor + 0.2);

                }
            }

            ///assign final color to image pixel
            output(x,y)->Red = (finalCol[0]<1 ? finalCol[0]:1)*255;
            output(x,y)->Green = (finalCol[1]<1 ? finalCol[1]:1)*255;
            output(x,y)->Blue = (finalCol[2]<1 ? finalCol[2]:1)*255;
            output(x,y)->Alpha = 1*255;

        }
    }
    output.WriteToFile("rays.bmp");
}

void MyGL::mousePressEvent(QMouseEvent *e) {
    this->setFocus(); //when click on myGL window it get focused
    //RenderRays();
    if(altPressed) { //switch to view mode
        oldX = e->x();
        oldY = e->y();

        right=false;
        left=false;
        middel=false;

        if(e->button() == Qt::LeftButton){ //to activate rotation mode
            left=true;
            //std::cout<<"clicked left button"<<std::endl;  //
        }
        if(e->button() == Qt::RightButton){ //to activate zooming mode
            right=true;
            //std::cout<<"clicked right button"<<std::endl;     //
        }
        if(e->button() == Qt::MidButton){ //to activate zooming mode
            middel=true;
            //std::cout<<"clicked middel button"<<std::endl;     //
        }
    }

    if(!altPressed) {//create ray from given pixel coordinate

        //set current rayD and rayP according to selected pixel
        generateRay(e->x(),e->y());

        testPerformed=0;
        //call final test intersection test for it

        sceneNode *result;

        if(octreeVisible){
            //**CAUTION**DO NOT DELETE NODE WHILE USING OCTREE//
            result = octreeIntersectionTest(rayP, rayD, mainOctree);
        } else {
            result = testIntersection(rayP, rayD, mainGraph.geometryNodes); //for simple intersection test
        }

        cout<<"no of geometries tested: "<<testPerformed<<endl;

        emit sig_sendSelectedItem((QTreeWidgetItem*)result);
    }

}

void MyGL::mouseMoveEvent(QMouseEvent *e){
    //std::cout<<"x: "<<e->x()<<", y: "<<e->y()<<std::endl;

    //if altPressed then switch to view mode
    if(altPressed) {
        if(left){ // camera movement
            int x,y;
            x=e->x() - oldX;
            y=e->y() - oldY;

            oldX=e->x();
            oldY=e->y();

            c.theta -= x*1;
            c.phi += y*1;
        }
        if(right){ //zooming
            int x,y;
            x=e->x() - oldX;
            y=e->y() - oldY;

            oldX=e->x();
            oldY=e->y();

            c.zoom += -1*x*0.1; //-1 for behave like maya
            c.zoom += y*0.1;
        }
        if(middel) { //panning of camera
            //It pan camera in viewing plane
            int x,y;
            x=e->x() - oldX;
            y=e->y() - oldY;
            oldX = e->x();
            oldY = e->y();

            vec4 cameraX, cameraY; // for camera plane X and Y axis
            cameraX = mat4::rotate(c.theta,0,1,0) * vec4(1,0,0,0);
            cameraY = mat4::rotate(c.phi,cameraX[0],cameraX[1],cameraY[2]) *
                      vec4(0,1,0,0);

            c.ref = c.ref + -x*cameraX*0.02 + y*cameraY*0.02; //0.02 for approximating panning with
                                                              //object movement
        }
    }

}


void MyGL::slot_addChild(sceneNode* node, sceneNode::geomType geometry, QString name){ //node and geomtry name

    static int childCount = 0;

    //Adding child to current selected node with default transofrmations
    if(node!=nullptr) { //Either any geometry is selected or not

        //add this child to mainGraph, if it has any geometry for on screen picking

        childCount+=1;
        QString childName;
        if(name=="") //setting default name
            childName = QString("child ")+QString::number(childCount);
        else
            childName=name;
        sceneNode* newChild = node->addChild(childName,
                       1,1,1,
                       0,0,0,
                       0,0,0,
                       vec4(0,0,0,1));

        if(geometry == sceneNode::SPHERE || geometry == sceneNode::CYLINDER || geometry == sceneNode::CUBE ) {
            mainGraph.geometryNodes.push_back(newChild);
            cout<<"New child for \""<<node->text(0).toUtf8().data()<<"\" created!"<<endl;  //
        }

        //adding geometry to newly child as stored name from QLineEdit
        if(geometry == sceneNode::SPHERE){
            newChild->addGeometry(&geom_sphere ,sceneNode::SPHERE, vec4(0,0,1,1));
        } else if( geometry == sceneNode::CYLINDER) {
            newChild->addGeometry(&geom_cylinder ,sceneNode::CYLINDER, vec4(0,0,1,1));
        } else if( geometry == sceneNode::CUBE) {
            newChild->addGeometry(&geom_cube ,sceneNode::CUBE, vec4(0,0,1,1));
        }
    }

}

//HW4 details:refer header
void MyGL::slot_removeGeomNodes(sceneNode * current){
    //if current node contain geometry, then find it and remove it from
    //geometryNodes vector of sceneGraph
      if(current->type != sceneNode::NONE){
        vector<sceneNode*>::iterator index;
        for(index=mainGraph.geometryNodes.begin(); index!=mainGraph.geometryNodes.end(); index++){
            if (*index == current)
                break;
        }
        mainGraph.geometryNodes.erase(index);
    }

    //iterate through all of it's children
    for(int i=0; i<current->childNode.size(); i++){
        //for each children recursively call this function if their children size is >0
        slot_removeGeomNodes(current->childNode[i]);
    }
}

//HW4 turn on/of octree visibility
void MyGL::slot_showOctree(bool in){
    octreeVisible = in;
}

//For HW4 ray intersection

bool sphereTest(vec4 P/*point*/, vec4 D/*direction*/, float &inT){
    // calculate A, B, C for eq. A*(t)2 + B*(t) + C = 0; //center C = <0,0,0,1> of sphere
    float A = D[0]*D[0] + D[1]*D[1] + D[2]*D[2];// A = Dx*Dx + Dy*Dy + Dz*Dz
    float B = 2*(D[0]*(P[0] - 0) + D[1]*(P[1] - 0) + D[2]*(P[2] - 0));    // B = 2( Dx(Px - Cx) + Dy(Py - Cy) + Dz(Pz - Dz) )
    float C = P[0]*P[0] + P[1]*P[1] + P[2]*P[2] - 0.5*0.5;// C = (Cx-Px)**2 + (Cy-Py)**2 + (Cz-Pz)**2 - r2

    float Dis = B*B - 4*A*C;// find discriminant
    if(Dis<0)// if discriminant<0
        return false;// return false

    float t = (-B - sqrt(Dis))/(2*A);// find first root as (-B-root(discriminant))/2*A

    if(t>0){// check first root > 0
       // then calculate t assign it it inT and return true
        inT=t;
        return true;
    }
    //otherwise find second root as (-B+root(discriminant))/2*A
    t = (-B + sqrt(Dis))/(2*A);

    //check if t<=0 then return false
    if(t<=0)
        return false;
    //calculate t assingnn it to inT and return true
    inT=t;
    return true;
}

bool cubeTest(vec4 P/*point*/, vec4 D/*direction*/, float &inT){
    //initialize Tnear and Tfar to -infinite and +infinite
    float tNear = -9999, tFar = 9999;
    //repete below for both Y and Z values of box
    ///box is bound from (-0.5,-0.5,-0.5) to (0.5,0.5,0.5)
    for(int i=0; i<3; i++){
        //First check for prallelism of ray from respective axis, here X axis
        if(D[i]==0) {//if: direction[0]=0, then it's parallel to X axis now
            if(-0.5/*Xmin*/>P[0] || 0.5/*Xmax*/<P[0])//check if  Xmin>point[0] or point[0]>Xmax then return false
                return false;
        }

        //else: find value of t0 and t1 by putting box's Xmin and Xmax in eq.
        // t = (X - Px)/Dx
        float t0 = (-0.5 - P[i])/D[i];
        float t1 = (0.5 - P[i])/D[i];
        if(t0>t1){//now if t0>t1 then swap them
            float temp=t0;
            t0=t1;
            t1=temp;
        }

        if(t0>tNear)//check if t0>Tnear, then Tnear=t0
            tNear=t0;
        if(t1<tFar)//check if t1<Tfar, then Tfar=t1
            tFar=t1;
    }

    if(tNear>tFar)//if Tmin>Tmax then return false
        return false;

    if(tNear<=0) // if Tmin<=0 then return false, as it is invalid ray intersect backward
        return false;

    //otherwise put inT=Tmin and return true
    inT=tNear;
    return true;
}

bool cylinderTest(vec4 P/*point*/, vec4 D/*direction*/, float &inT){
    //calculate J,H,K for equation, where
        //J=DxC, H=(P-Cs)xC, K=r**2 * C**2; here Cs=bottom point of cylinder
                                               //C=vector from bootom to top point of cylinder
    ///for cylinder Cs <0,-0.5,0,1>, Ce <0,0.5,0,1> and C= Ce-Cs = <0,1,0,0>
    /// radius r = 0.5;
    float r = 0.5;
    vec4 Cs (0,-0.5,0,1);
    vec4 C (0,1,0,0);
    vec4 J = cross(D,C);
    vec4 H = cross((P-Cs),C);
    float K = r*r * dot(C,C);

    //calculate A,B,C for eq. A*t**2 +B*t + C = 0;
    //where, A=J.J, B=2*(H.J), C=(H.H - K)
    float A1 = dot(J,J);
    float B1 = 2*dot(H,J);
    float C1 = dot(H,H)-K;

    float D1 = B1*B1 - 4*A1*C1;// find discriminant

    //Declare global minT which was used as final point of intersection with cylinder
    //initialize it with +infinity
    float minT = 9999;

    ///Check for end caps
         ///
    bool findCaps = false; //use when discriminant is negative
    //assign a point that lies on plane of each side of end caps
    vec4 tbQ[2] = { vec4(999,0.5,999,1), vec4(999,-0.5,999,1) }; //top and bottom plane random point
    vec4 planeNorm (0,1,0,0);
    vec4 tbCentre[2] = { vec4(0,0.5,0,1), vec4(0,-0.5,0,1)  }; //top and bottom centre
    for(int i=0; i<2; i++) {
        //calculate intersection t for each plane then check whether distance of point with
        float t = dot((tbQ[i] - P),planeNorm)/dot(D,planeNorm);
        vec4 newPoint = P + t*D;
        if(length(newPoint-tbCentre[i]) <= r){ // center of cap is less then or eqaul to radius
            //if true then compare it with minT if it found less then assign it to minT
            findCaps = true;
            if(t<minT)
                minT=t;
        }

    }
        ///

    if(D1<0){// if discriminant<0
        if(findCaps){ //if we found intersection with end caps then
            inT = minT;

            //cout<<"cap intersect but surface not"<<endl;
            if(minT<=0) //if minT is negative or 0 then we discard it
                return false;

            return true;
        }
        return false;// return false
    }
    float t = (-B1 - sqrt(D1))/(2*A1);// find first root as (-B-root(discriminant))/2*A

    ///now test if calculated point lies in height of cylinder
    float halfHeight=0.5;
    vec4 point = P+t*D;

    if(t>0 && (point[1]>=-halfHeight && point[1]<=halfHeight)){// check first root > 0 and height of point
       // then assign t to inT and return true
        if(t<minT) {
            inT=t;
        } else if(findCaps) {
            inT=minT;
        }
        return true;
    } else {
        //otherwise find second root as (-B+root(discriminant))/2*A
        t = (-B1 + sqrt(D1))/(2*A1);
        point = P + t*D;//calculate point that it represents

        if(point[1]>=-halfHeight && point[1]<=halfHeight){//check whether it's Y-axis is in between cylinder
            //now if it's t<minT then assign t to inT and and return true
            if(t<minT){
                //cout<<"getting other root and assigning it"<<endl;
                if(t<=0) //if t<=0 then ray intersect backward
                    return false;
                inT=t;
                return true;
            }
        }
        if(findCaps){ //other wise if we hit end caps then return current minT with true return
            if(minT<=0) //if ray hitting negatively
                return false;
            inT=minT;
            return true;
            cout<<"SENDING TRUE FOR HIT CAPS"<<endl;

        }
    }

    return false;
}

//this get point, direction of ray and vector of scene nodes contain geometry only for which it need to test
//ray intersection test
sceneNode* MyGL::testIntersection(vec4 point, vec4 direction, std::vector<sceneNode *> &geometries,
       /*next para. for rayTracer*/float *rayTraT, mat4 *rayTraM, bool needRayTraM) {
    //declare global geometry and minT for minimam t which define final geometry
    sceneNode *finalGeom=nullptr;
    float minT = 9999;

    //start traversing all node contain geometry in sceneGraph
    //std::cout<<"current contain geometries of: "<<std::endl;  //
    for(int i=0; i< geometries.size(); i++) {
        testPerformed++; //analysis on how many geometries tested
        //declare matrix conatain resultaint transformation initialize it to unit matrix
        mat4 resultMat (1);
        sceneNode *currentNode = geometries[i];
        //std::cout<<currentNode->text(0).toUtf8().constData()<<std::endl;    //

        //# start for current node pre multiply it's all transformation to result matrix
        while(currentNode!=nullptr){
            resultMat = currentNode->getResultaint() * resultMat ;
            currentNode=currentNode->getParent();
            //continues call above # step with current's parent node until parent=nullptr;
        }

        mat4 inverseResultMat = la::inverse(resultMat);
        //calculate new point and direction ray by multiplying them with inverse of result matrix
        vec4 newPoint =  inverseResultMat*point;
        vec4 newDirection = inverseResultMat*direction;

        //begin test for corresponding geometry
        currentNode = geometries[i];
        float outT;
        bool result = false;
        switch (currentNode->type) {
        case (sceneNode::SPHERE):
            result = sphereTest(newPoint, newDirection,outT);
            break;

        case (sceneNode::CYLINDER):
            result = cylinderTest(newPoint, newDirection,outT);
            break;

        case (sceneNode::CUBE):
            result = cubeTest(newPoint, newDirection,outT);
            break;

        default:
            break;
        }
        //if get true, then calculate point in obect space by objectP = newP + t*newD;
        if(result) {
            vec4 objectP = newPoint + outT* newDirection;
            // transform it to world space by multiplying it with resultant matrix we get worldP
            vec4 worldP = resultMat * objectP;
            // now calculate worldT = length(camera.eye - worldP);
            float worldT = length(c.getPosition() - worldP);
            // check worldT<minT, if true then assign minT=worldT and finalGeom=this geometry;
            if(worldT<minT){
                minT=worldT;
                finalGeom=currentNode;
                if(needRayTraM){//only for ray tracer
                    *rayTraT = outT; //object space T
                    if(rayTraM!=nullptr)
                    *rayTraM = resultMat; //reslutaint matrix for this node
                }
            }
        }

    }

//    if(finalGeom == nullptr){ //
//        cout<<"final geometry is nullptr"<<endl;  //
//    } //
    //now we get resultant geometry
    return finalGeom;
}


//Octree from here
void recurBuildOctree(octree &tree){

    ///first check wheter it contain < 2 full geometries if yes then return
     if(tree.completeGeom < 2)
        return;

    ///divide it in 8 part, also adding into tree
    //front side
    octree *c = new octree( tree.minMaxX[0]                   , (tree.minMaxX[0]+tree.minMaxX[1])/2, //front top left
                           (tree.minMaxY[0]+tree.minMaxY[1])/2, tree.minMaxY[1],
                           (tree.minMaxZ[0]+tree.minMaxZ[1])/2, tree.minMaxZ[1]);
    tree.children.push_back(c); //adding to tree's child vector

    c = new octree((tree.minMaxX[0]+tree.minMaxX[1])/2, tree.minMaxX[1] , //front top right
                   (tree.minMaxY[0]+tree.minMaxY[1])/2, tree.minMaxY[1],
                   (tree.minMaxZ[0]+tree.minMaxZ[1])/2, tree.minMaxZ[1]);
    tree.children.push_back(c);

    c = new octree( tree.minMaxX[0]                   , (tree.minMaxX[0]+tree.minMaxX[1])/2, //front bottom left
                    tree.minMaxY[0]                   , (tree.minMaxY[0]+tree.minMaxY[1])/2,
                   (tree.minMaxZ[0]+tree.minMaxZ[0])/2, tree.minMaxZ[1]);
    tree.children.push_back(c);

    c = new octree((tree.minMaxX[0]+tree.minMaxX[1])/2, tree.minMaxX[1], //front bottom right
                    tree.minMaxY[0]                   , (tree.minMaxY[0]+tree.minMaxY[1])/2,
                   (tree.minMaxZ[0]+tree.minMaxZ[0])/2, tree.minMaxZ[1]);
    tree.children.push_back(c);

    //back side
    c = new octree( tree.minMaxX[0]                   , (tree.minMaxX[0]+tree.minMaxX[1])/2, //back top left
                   (tree.minMaxY[0]+tree.minMaxY[1])/2, tree.minMaxY[1],
                    tree.minMaxZ[0]                   ,(tree.minMaxZ[0]+tree.minMaxZ[1])/2);
    tree.children.push_back(c);

    c = new octree((tree.minMaxX[0]+tree.minMaxX[1])/2, tree.minMaxX[1] , //back top right
                   (tree.minMaxY[0]+tree.minMaxY[1])/2, tree.minMaxY[1],
                    tree.minMaxZ[0]                   ,(tree.minMaxZ[0]+tree.minMaxZ[1])/2);
    tree.children.push_back(c);

    c = new octree( tree.minMaxX[0]                   ,(tree.minMaxX[0]+tree.minMaxX[1])/2, //back bottom left
                    tree.minMaxY[0]                   ,(tree.minMaxY[0]+tree.minMaxY[1])/2,
                    tree.minMaxZ[0]                   ,(tree.minMaxZ[0]+tree.minMaxZ[1])/2);
    tree.children.push_back(c);

    c = new octree((tree.minMaxX[0]+tree.minMaxX[1])/2, tree.minMaxX[1], //back bottom right
                    tree.minMaxY[0]                   , (tree.minMaxY[0]+tree.minMaxY[1])/2,
                    tree.minMaxZ[0]                   , (tree.minMaxZ[0]+tree.minMaxZ[1])/2);
    tree.children.push_back(c);


    ///for each child iterate through all "tree" node's geometry and
    octree *currentN;
    sceneNode *currentG;
    for(int node=0; node<tree.children.size(); node++){
        currentN = tree.children[node];
        for(int geom=0; geom<tree.geometryNodes.size(); geom++) {
            currentG = tree.geometryNodes[geom];

            //check whether their bounding box lyes in child's box
            //check by this formula (NodeMax > GeomMin)&&(NodeMin < GeomMax)
            bool find = false;
            if( (currentN->minMaxX[1] > currentG->minMaxX[0])&&(currentN->minMaxX[0]<currentG->minMaxX[1]) )//X-axis check
                if((currentN->minMaxY[1] > currentG->minMaxY[0])&&(currentN->minMaxY[0]<currentG->minMaxY[1]))//Y-axis check
                    if((currentN->minMaxZ[1] > currentG->minMaxZ[0])&&(currentN->minMaxZ[0]<currentG->minMaxZ[1]))//Z-axis check
                        find = true;
            if(find){//if yes then add this to child's geometry node and
                //std::cout<<"found geom"<<std::endl;  //
                currentN->addGeometry(currentG);

                //also check whether it fit's completely or not in this box
                //using formula (NodeMax > GeomMin)&&(NodeMax > GeomMax) && (NodeMin <GeomMin)&&(NodeMin<GeomMax)
                if( (currentN->minMaxX[1]>currentG->minMaxX[0])&&(currentN->minMaxX[1]>currentG->minMaxX[1]) &&//X-axis check
                    (currentN->minMaxX[0]<currentG->minMaxX[0])&&(currentN->minMaxX[0]<currentG->minMaxX[1]))
                    if( (currentN->minMaxY[1]>currentG->minMaxY[0])&&(currentN->minMaxY[1]>currentG->minMaxY[1]) &&//Y-axis check
                        (currentN->minMaxY[0]<currentG->minMaxY[0])&&(currentN->minMaxY[0]<currentG->minMaxY[1]))
                        if( (currentN->minMaxZ[1]>currentG->minMaxZ[0])&&(currentN->minMaxZ[1]>currentG->minMaxZ[1]) &&//Z-axis check
                            (currentN->minMaxZ[0]<currentG->minMaxZ[0])&&(currentN->minMaxZ[0]<currentG->minMaxZ[1]))
                    //if yes then increment this child's completeGeom
                            currentN->completeGeom+=1;
            }
        }
    }


    ///now for all children contain completeGeom>=2, recursivly call this function
    for(int i=0; i<tree.children.size(); i++) {
        currentN = tree.children[i] ;
        if( currentN->completeGeom >= 2)
            recurBuildOctree(*currentN);
    }
}

void MyGL::buildOctree() {
    //call startRoot of root octree whic initialize it'b box, geomery and no.of full geometries it contain
    mainOctree.startRoot(&mainGraph);

    //call recursion function that take a octree and subdivide in 4 parts if it conation >2 full geometries
    recurBuildOctree(mainOctree);
}

bool octBoxTest(vec4 P/*point*/, vec4 D/*direction*/, float &inT, vec4 min/*minimum vertex*/, vec4 max/*maximum vertex*/){
    //initialize Tnear and Tfar to -infinite and +infinite
    float tNear = -9999, tFar = 9999;

    //repete below for both Y and Z values of box
    ///box is bound from min to max
    for(int i=0; i<3; i++){
        //First check for prallelism of ray from respective axis, here X axis
        if(D[i]==0) {//if: direction[0]=0, then it's parallel to X axis now
            if(min[i]/*Xmin*/>P[0] || max[i]/*Xmax*/<P[0])//check if  Xmin>point[0] or point[0]>Xmax then return false
                return false;
        }

        //else: find value of t0 and t1 by putting box's Xmin and Xmax in eq.
        // t = (X - Px)/Dx
        float t0 = (min[i] - P[i])/D[i];//Xmin
        float t1 = (max[i] - P[i])/D[i];//Xmax
        if(t0>t1){//now if t0>t1 then swap them
            float temp=t0;
            t0=t1;
            t1=temp;
        }

        if(t0>tNear)//check if t0>Tnear, then Tnear=t0
            tNear=t0;
        if(t1<tFar)//check if t1<Tfar, then Tfar=t1
            tFar=t1;
    }

    if(tNear>tFar)//if Tmin>Tmax then return false
        return false;
    //otherwise put inT=Tmin and return true
    inT=tNear;
    return true;
}

sceneNode * MyGL::octreeIntersectionTest(vec4 point, vec4 direction , octree &oTree){
    //for current oTree test whether it hits or not current
    float outT;
    vec4 minVertex (oTree.minMaxX[0], oTree.minMaxY[0], oTree.minMaxZ[0], 1);
    vec4 maxVertex (oTree.minMaxX[1], oTree.minMaxY[1], oTree.minMaxZ[1], 1);
    bool result = octBoxTest(point, direction, outT, minVertex, maxVertex );

    if(!result){//if not hit return nullptr
        return nullptr;
    }

    //if it is leaf i.e. children.size() < 1 , then call "testIntersection" by passing it's children vector list
    if(oTree.children.size() < 1){
        return testIntersection(point, direction, oTree.geometryNodes);//return result of calling this function
    }

    //other wise intersect ray with children box to find minimum t value for each box, and
    float outTs[8][2]; //1st column contain index of child, 2nd contain corresponding t
                       //and 8 Row is maximum no of child that hitten by ray
    int totalHit = 0;//to store no. boxes hits rat
    octree *current;
    for(int i=0; i<8; i++){
        current =  oTree.children[i];
        minVertex = vec4(current->minMaxX[0], current->minMaxY[0], current->minMaxZ[0], 1);
        maxVertex = vec4(current->minMaxX[1], current->minMaxY[1], current->minMaxZ[1], 1);

        result = octBoxTest(point, direction, outT, minVertex, maxVertex);//begin test
        if(result){ // if ray hits
            outTs[totalHit][0] = i;
            outTs[totalHit][1] = outT;
            totalHit++;
        }
    }
    //sort it's children increasing value of t
    for(int i=0; i<totalHit; i++){ //Using Quick Sort Algorithm
        for(int j=i+1; j<totalHit; j++){
            if(outTs[i][1] > outTs[j][1]){
                //Changing both t and index
                float tempIdx = outTs[i][0];
                float tempT = outTs[i][1];

                outTs[i][0] = outTs[j][0];
                outTs[i][1] = outTs[j][1];

                outTs[j][0] = tempIdx;
                outTs[j][1] = tempT;
            }
        }
    }

    //start with smallest t and also to childeren where ray hits
    sceneNode *final;
    for(int i =0 ; i<totalHit; i++){
        //recursively call this function with that child
        final = octreeIntersectionTest( point, direction, *(oTree.children[(int)outTs[i][0]]) );
        //if it return !=nullptr then return it
        if(final!=nullptr)
            return final;
    }
    //at end return nullptr
    return nullptr;
}
