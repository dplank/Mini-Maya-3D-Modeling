#ifndef CAMERA_H
#define CAMERA_H

#include <linear_algebra/mat4.h>

class camera
{
public:
    // for view matrix
    float theta, phi;
    float zoom;
    vec4 ref; // view reference for paning of camera

    // for projection matrix
    float fovy;
    float width, height;
    float nearP, farP;

    camera();
    camera(float inWidth, float inHeight );
    ~camera();

    mat4 perspective();
    mat4 view();
    mat4 orthogonal();
    vec4 getPosition(); // return position of camera
    vec4 getRight();
    vec4 getUp();
};

#endif // CAMERA_H
