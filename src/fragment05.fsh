#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;
uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float time;

void main()
{
    vec4 colorKitten = texture(texKitten, Texcoord);
    vec4 colorPuppy = texture(texPuppy, Texcoord);
    float t = (sin(time * 40) + 1) /2;
    outColor = mix(colorKitten, colorPuppy, t);
}
