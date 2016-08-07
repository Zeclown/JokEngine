#version 330 core
layout (location = 0) in vec4 vPosition;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat2 frameSize;
uniform int frame;

void main()
{
    vec2 coordsArray;
    int nbColumns=1/frameSize.x;
    int nbRows=1/frameSize.y;
    int column = frame % nbColumns;
    int row= frame/nbColumns;
    vec2 offset;
    offset.x=column*frameSize.x;
    offset.y=column*frameSize.y;
    texCoords = vertex.zw+offset;
    gl_Position = projection * model * vec4(vPosition.xy, 0.0, 1.0);
}
