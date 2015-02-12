#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;
uniform sampler2D tex;
uniform float time;

void main()
{
    if (Texcoord.y < 0.5)
    {
        outColor = texture(tex, Texcoord);// * vec4(Color, 1.0);
    } else
    {
        outColor = texture(tex, vec2(Texcoord.x + sin(Texcoord.y * 60.0 + time * 100.0)/30, 1 - Texcoord.y));
    }
}
