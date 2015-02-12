#version 150 core

// Fragment Shader

in vec3 Color;
out vec4 outColor;

void main()
{
    // inverse color
    vec3 inverseColor = 1 - Color;
    outColor = vec4(inverseColor, 1.0);

    outColor = vec4(Color, 1.0);
}
