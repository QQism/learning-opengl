#version 150 core

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform float time;

void main()
{
    Color = color;
    Texcoord = texcoord;
    vec2 newPosition = position * (sin(time * 100) + 1);
    gl_Position = proj * view * model * vec4(newPosition, 0.0, 1.0);
}
