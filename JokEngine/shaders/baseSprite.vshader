#version 330 core
layout (location = 0) in vec2 vPosition;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat2 frameSize;
uniform int frame;

void main()
{
    vec2 coordsArray[6];
    int nbColumns=1/frameSize.x;
    int nbRows=1/frameSize.y;
    int column = frame % nbColumns;
    int row= frame/nbColumns;
    coordsArray[0]=(column*frameSize.x, 1.0f-row*frameSize.y);
    coordsArray[1]=(frameSize.x+frameSize.x*column, 1.0f-(frameSize.y+frameSize.y*row));
    coordsArray[2]=(column*frameSize.x, 1.0f-(frameSize.y+frameSize.y*row));
    coordsArray[3]=(column*frameSize.x, 1.0f-row*frameSize.y);
    coordsArray[4]=(frameSize.x+frameSize.x*column, 1.0f-row*frameSize.y));
    coordsArray[5]=(frameSize.x+frameSize.x*column, 1.0f-(frameSize.y+frameSize.y*row));

    gl_Position = projection * model * vec4(vPosition.xy, 0.0, 1.0);
}
