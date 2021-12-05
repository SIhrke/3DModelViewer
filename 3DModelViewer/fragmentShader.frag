#version 140
uniform vec3 eyePosition;
uniform vec4 lightDirection;

in vec3 fragVertex;
in vec3 fragNormal;

out vec4 fragmentColor;


void main()
{

    vec3 diffuseColor=vec3(1.0,1.0,1.0);
    vec3 ambientColor=vec3(0.8,0.8,0.8);
    diffuseColor*=(1.0/3.0*max(dot(lightDirection.xyz, fragNormal),0.0)+1.0/3.0*max(dot(vec3(0,1,1), fragNormal),0.0)+1.0/3.0*max(dot(vec3(0,-1,-1), fragNormal),0.0));

    float ambientMix=0.3;
    float diffuseMix=0.4;
    float specularMix=0.3;

    vec3 eyeDirection=normalize(fragVertex-eyePosition);
    vec3 H=normalize(eyeDirection+lightDirection.xyz);
    
    vec3 color=ambientMix*ambientColor+diffuseMix*diffuseColor+specularMix*pow(max(dot(H,fragNormal),0.0),30.0);
    fragmentColor = vec4(color, 1.0);
}