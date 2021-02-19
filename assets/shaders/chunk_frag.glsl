#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, v_texCoord);
    // color = vec4(v_texCoord, 0.0, 1.0);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
}
