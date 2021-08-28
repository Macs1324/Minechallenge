#version 330

in vec2 fUv;

uniform sampler2D sprite;

out vec4 color;

void main()
{
    color = texture(sprite, fUv);
}
