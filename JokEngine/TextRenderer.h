#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"
#include "TextRenderingService.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint textureID;   // ID handle of the glyph texture
	glm::ivec2 size;    // Size of glyph
	glm::ivec2 bearing; // Offset from baseline to left/top of glyph
	GLuint advance;     // Horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer : public TextRenderingService
{
public:
	// Constructor
	TextRenderer(GLuint width, GLuint height);
	// Pre-compiles a list of characters from the given font
	void Load(std::string font, GLuint fontSize);
	// Renders a string of text using the precompiled list of characters
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
	// Holds a list of pre-compiled Characters
	std::map<GLchar, Character> characters;
	// Shader used for text rendering
	Shader textShader;
private:
	// Render state
	GLuint VAO, VBO;
};


#endif // !TEXT_RENDERER_H

