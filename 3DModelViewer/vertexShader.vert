#version 140
uniform mat4 MVP;
uniform mat4 mvpNormal;

in vec3 vertex;
in vec3 normal;
out vec3 color;
void main()
{
   gl_Position = MVP*vec4(vertex, 1.0);

    vec3 light=vec3(0,0,1);
    float k=1.0;
    vec3 diffuseColor=vec3(1.0,0.0,0.0);
    diffuseColor*=dot(light,normal);

   color=diffuseColor*dot(diffuseColor,diffuseColor);
}
