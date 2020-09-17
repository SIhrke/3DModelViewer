#version 140

in vec3 fragNormal;
in vec3 color;
out vec4 fragmentColor;


void main()
{
    fragmentColor = vec4(color, 1.0);
}