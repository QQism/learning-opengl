#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;
uniform sampler2D tex;

void main()
{
    if (Texcoord.y < 0.5)
    {
        outColor = texture(tex, Texcoord);// * vec4(Color, 1.0);
    } else
    {
        outColor = texture(tex, vec2(Texcoord.x, 1 - Texcoord.y));
    }
}
