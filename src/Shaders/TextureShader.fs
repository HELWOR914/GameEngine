#version 330 core
out vec4 OutColor;

in vec2 texcoord;

uniform sampler2D ourTexture;

void main()
{
	OutColor = texture(ourTexture, texcoord);
}