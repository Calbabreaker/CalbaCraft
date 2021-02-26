#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

uniform vec3 u_blockOffset;
uniform mat4 u_viewProjection;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProjection * (a_position + vec4(u_blockOffset, 1.0));
}
