#version 330 core
layout (location = 0) in vec4 vPosition;
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
    if(nbRows>1)
    {
      coordsArray.y= frameSize.y*nbRows;
    }
    offset.x=column*frameSize.x;
    offset.y=0-(column*frameSize.y);
    texCoords = coordsArray.xy+offset;
    gl_Position = projection * model * vec4(vPosition.xy, 0.0, 1.0);
}
