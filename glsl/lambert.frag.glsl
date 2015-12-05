#version 150
// ^ Change this to version 130 if you have compatibility issues

//This is a fragment shader. If you've opened this file first, please open and read lambert.vert.glsl before reading on.
//Unlike the vertex shader, the fragment shader actually does compute the shading of geometry.
//For every pixel in your program's output screen, the fragment shader is run for every bit of geometry that particular pixel overlaps.
//By implicitly interpolating the position data passed into the fragment shader by the vertex shader, the fragment shader
//can compute what color to apply to its pixel based on things like vertex position, light position, and vertex color.

uniform vec4 u_Color;//The color with which to render this instance of geometry.

//These are the interpolated values out of the rasterizer, so you can't know
//their specific values without knowing the vertices that contributed to them
in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;

out vec4 out_Col;//This is the final output color that you will see on your screen for the pixel that is currently being processed.

//uniform mat4 u_ModelInvTr;  //
//in vec4 fs_vertPos; //
//uniform mat4 u_Model;

void main()
{

    // Material base color (before shading)
    vec4 diffuseColor = u_Color;
    //vec4 Nor1 = (u_ModelInvTr) * (normalize(fs_Nor));  //
    //Nor1= normalize(Nor1); //

    //vec4 vertPos1 = u_Model*fs_vertPos;//
    //vec4 origin = u_Model * vec4(0,0,0,1);//
    //origin = vec4(origin.xyz/origin.w,1); //

    //Nor1 = normalize(vertPos1 - origin);  //

    //vertPos1 = vec4(vertPos1.xyz/vertPos1.w, 1);

    //vec4 light1 = (vec4(0, 8, 0, 1) - vertPos1);    // vec4(5, 5, 3, 1)

    // Calculate the diffuse term for Lambert shading
    float diffuseTerm = dot(normalize(fs_Nor), normalize(fs_LightVec));
    // Avoid negative lighting values
    diffuseTerm = clamp(diffuseTerm, 0, 1);

    float ambientTerm = 0.2;

    float lightIntensity = diffuseTerm + ambientTerm;   //Add a small float value to the color multiplier
                                                        //to simulate ambient lighting. This ensures that faces that are not
                                                        //lit by our point light are not completely black.

    // Compute final shaded color
    out_Col = vec4(diffuseColor.rgb * lightIntensity, diffuseColor.a);

        //out_Col = vec4(1,0,0,1);
}
