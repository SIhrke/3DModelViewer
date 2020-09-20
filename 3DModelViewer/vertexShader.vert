#version 140
uniform mat4 MVP;
uniform mat4 mvpNormal;
uniform vec4 lightDirection;

in vec3 vertex;
in vec3 normal;
out vec3 color;
void main()
{
   gl_Position = MVP*vec4(vertex, 1.0);

    float k=1.0;
    vec3 diffuseColor=vec3(0.4,0.4,0.4);
    vec3 ambientColor=vec3(0.2,0.2,0.2);
    diffuseColor*=dot(lightDirection.xyz,normal);

   color=ambientColor+diffuseColor*dot(diffuseColor,diffuseColor);
}
