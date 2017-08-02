#version 330 core
layout (location = 0) in vec4 vPosition; //xy =position, zw=textureCoords
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 frameSize;
uniform int frame;

void main()
{
    vec2 coordsArray;
    int nbColumns=int(1/frameSize.x);
    int nbRows=int(1/frameSize.y);
    int column = frame % nbColumns;
    int row= frame/nbColumns;
    vec2 offset;
    coordsArray=vPosition.zw;
    coordsArray.x=coordsArray.x*frameSize.x;
    coordsArray.y=coordsArray.y*frameSize.y;

    offset.x=column*frameSize.x;
    offset.y=1-(row*frameSize.y);
    texCoords = coordsArray.xy+offset;
    gl_Position = projection * model * vec4(vPosition.xy, 0.0, 1.0);
}
