#pragma once
#include <string>
#include "TextRenderingService.h"
#include "Component.h"
class TextUI:public ComponentCloneable<Component,TextUI>
{
	using ComponentCloneable<Component, TextUI>::ComponentCloneable;
public:
	GLuint drawOrder;
	std::string text;
	GLboolean worldCoordinates;
	GLboolean justify;
	glm::vec3 color;
	glm::vec2 position;
	GLfloat scale;
	void DrawText(TextRenderingService &renderer);
};

