#version 150 core

in vec2 position;

// Vertex Shader
void main()
{
    // upside-down
    vec2 new_position = vec2(position.x, -position.y);
    gl_Position = vec4(new_position, 0.0, 1.0);
}
