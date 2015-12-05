#include "camera.h"

#define PI 3.141

using namespace std;

camera::camera() {
    ref = vec4(0,0,0,1);
    theta = 0; phi = 0;
    zoom = 10;

    fovy = 45;
    nearP = 1;
    farP = 200;
    width = 2;
    height = 1;

    printf("11 hari hari ");
}

camera::camera(float inWidth, float inHeight) {
    theta = 0; phi = 0;
    zoom = 5;
    nearP = 1;
    farP = 100;


    width = inWidth;
    height = inHeight;
}

mat4 camera::view() {
    //***// angle in radian
    float thetaRad = theta * PI / 180; // rotation measured from Y-Z plan about Y-axis
    float phiRad = phi * PI / 180; // rotation measured from Z-X plan about X-axis


    //***// calculation of position of camera
    vec4 position (zoom * cos(phiRad) * sin(thetaRad) ,
                   zoom * sin(phiRad), //Move up as "phi" increase
                   zoom * cos(phiRad) * cos(thetaRad),
                   1);

    //***// calculate 3 vector of camera axis or of plane of projection
    // [-Z axis]
    vec4 secAxis = mat4::rotate(theta,0,1,0)*vec4(0,0,-1,0);
    secAxis = mat4::rotate(90,0,1,0) * secAxis;
    vec4 Zaxis = (mat4::rotate(phi,secAxis[0],secAxis[1],secAxis[2])*mat4::rotate(theta, 0,1,0)) * vec4(0,0,-1,0);

    // [Y axis]
    vec4 Yaxis = mat4::rotate(phi,secAxis[0],secAxis[1],secAxis[2])*vec4(0,1,0,0);

    // [X axis]
   vec4 Xaxis = cross(Zaxis, Yaxis);
   Xaxis /= length(Xaxis);


    //***// Creating resultant matrix
    mat4 rot (Xaxis,
              Yaxis,
              -1*Zaxis, //placing Z axis of camera at -Z axis
              vec4(0,0,0,1));

   mat4 trans (vec4(1, 0, 0, -(position[0]+ref[0])),
               vec4(0, 1, 0, -(position[1]+ref[1])),
               vec4(0, 0, 1, -(position[2]+ref[2])),
               vec4(0, 0, 0, 1));


    mat4 out = rot * trans;

    return out;
}

mat4 camera::perspective() {
    float aspect = width/height;
    float top = nearP * tan((fovy/2) * PI / 180);
    float bottom = -top;
    float right = top*aspect;
    float left = -right;


    mat4 out = mat4( vec4(2*nearP/(right-left), 0             , (right+left)/(right-left)             ,0 ),
                     vec4(0             , 2*nearP/(top-bottom), (top+bottom)/(top-bottom)             ,0 ),
                     vec4(0             , 0             , (nearP)/(farP-nearP), -nearP*farP/(farP-nearP)),
                     vec4(0             , 0             , -1             , 0)
                    );

//    double theta=fovy/2;
//        double d = 1/tan(theta*PI/180);
//        double A=-(farP+nearP)/(farP-nearP);
//        double B=-2*farP*nearP/(farP-nearP);

//        mat4 out=mat4(vec4(d/aspect,0 ,0 ,0),
//                      vec4(0       ,d ,0 ,0),
//                      vec4(0       ,0 ,A ,B),
//                      vec4(0       ,0 ,-1,0));
    //out = (out);


//    cout<<"projection matrix: "<<out;

    return out;
}

mat4 camera::orthogonal() {
    float aspect = width/height;
    float top = nearP * tan((fovy/2) * PI/180);
    float bottom = -top;
    float right = top*aspect;
    float left = -right;

    float nearPCoord = -nearP;
    float farPCoord = -farP;

    //cout<<"fovy: "<<fovy<<endl;

    mat4 out ( vec4( 2/(right-left), 0             , 0                       , -1*(right+left)/(right-left) ),
               vec4( 0             , 2/(top-bottom), 0                       , -1*(top+bottom)/(top-bottom)),
               vec4( 0             , 0             , 2/(farPCoord-nearPCoord), -1*(farPCoord+nearPCoord)/(farPCoord-nearPCoord)),
               vec4( 0             , 0             , 0                       , 1)
               );
    return out;
}

vec4 camera::getPosition() {
    float thetaRad = theta * PI / 180; // rotation measured from Y-Z plan about Y-axis
    float phiRad = phi * PI / 180; // rotation measured from Z-X plan about X-axis

    vec4 position (zoom * cos(phiRad)* sin(thetaRad),
                   zoom * sin(phiRad),
                   zoom * cos(phiRad) * cos(thetaRad),
                   1);
    return position;
}

vec4 camera::getRight(){
    vec4 right = mat4::rotate(theta, 0,1,0) * vec4(1,0,0,0); //rotating x axis
    return right;
}

vec4 camera::getUp() {

    vec4 rotAbout = mat4::rotate(theta, 0,1,0)*vec4(1,0,0,0);

    vec4 up = mat4::rotate(phi, -rotAbout[0], -rotAbout[1], -rotAbout[2])*vec4(0,1,0,0);

    return up;
}

camera::~camera()
{

}

