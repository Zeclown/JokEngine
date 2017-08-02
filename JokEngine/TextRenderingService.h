#ifndef TEXT_RENDERING_SERVICE_H
#define TEXT_RENDERING_SERVICE_H
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>

//The default UI Text Service to render text
class TextRenderingService
{
public:
	// Pre-compiles a list of characters from the given font
	virtual void Load(std::string font, GLuint fontSize)=0;
	// Renders a string of text using the precompiled list of characters
	virtual void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,GLboolean worldCoordinates,GLboolean justify, glm::vec3 color = glm::vec3(1.0f))=0;
};

#endif // !TEXT_RENDERING_SERVICE_H

