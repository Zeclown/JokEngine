#version 330 core
layout (location = 0) in vec4 vPosition; // <vec2 position, vec2 texCoords>
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    texCoords = vPosition.zw;
    gl_Position = projection * model * vec4(vPosition.xy, 0.0, 1.0);
}
