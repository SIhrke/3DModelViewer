#version 110
uniform mat4 MVP;
attribute vec3 vertex;
void main()
{
   gl_Position = MVP*vec4(vertex, 1.0);
}