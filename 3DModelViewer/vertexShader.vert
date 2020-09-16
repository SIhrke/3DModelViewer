#version 140
uniform mat4 MVP;

in vec3 vertex;
out vec3 fragNormal;
void main()
{
   gl_Position = MVP*vec4(vertex, 1.0);
}

