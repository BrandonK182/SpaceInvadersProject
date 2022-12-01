#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 tex;

out vec3 color;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos, 1.0f);
    color = aColor;
    texCoord = tex;
}