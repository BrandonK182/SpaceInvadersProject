#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture1;

void main()
{
    FragColor = texture(ourTexture1, texCoord);
}