#version 330 core

layout(location = 0) out vec4 color;

uniform float u_red;

void main()
{
    color = vec4(u_red, 1.0f, 1.0f, 1.0f);
}
