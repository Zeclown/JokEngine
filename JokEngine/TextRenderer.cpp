#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.h"
#include "Resource_Manager.h"
#include "Game.h"


TextRenderer::TextRenderer(GLuint width, GLuint height)
{
	// Load and configure shader
	this->textShader = ResourceManager::LoadShader("shaders/text.vshader", "shaders/text.fshader", nullptr, "text");
	this->textShader.SetMatrix4("projection", Game::GetInstance().GetCameraService().GetUICamera()->GetViewMatrix(), GL_TRUE);
	this->textShader.SetInteger("text", 0);
	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void TextRenderer::Load(std::string font, GLuint fontSize)
{
	// First clear the previously loaded Characters
	this->characters.clear();
	// Then initialize and load the FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) 
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	return;
	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	return;
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Precompiling first 128 characters
	for (GLubyte c = 0; c < 128; c++) 
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph "+c << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}



void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, GLboolean worldCoordinates, GLboolean justify, glm::vec3 color)
{
	this->textShader.SetMatrix4("projection", Game::GetInstance().GetCameraService().GetUICamera()->GetViewMatrix(), GL_TRUE);
	// Activate corresponding render state	
	this->textShader.Use();
	this->textShader.SetVector3f("textColor", color);
	if (worldCoordinates)
	{
		glm::mat4 model;
		this->textShader.SetMatrix4("projection", Game::GetInstance().GetCameraService().GetMainCamera()->GetViewMatrix(), GL_TRUE);
		scale /= 20;
		glm::translate(model, glm::vec3(x, y, 0));
		textShader.SetMatrix4("model", model);
	}
	else
	{
		textShader.SetMatrix4("model", glm::mat4(1));
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);



	if (justify)//we need to calculate the left offset
	{
		std::string::const_iterator i;
		GLfloat startX = x;
		GLfloat endX = startX;
		for (i = text.begin(); i != text.end(); i++)
		{
			Character ch = characters[*i];
			endX+=(ch.advance / 64) * scale;
		}
		GLfloat offsetX= (endX-startX)/2;
		x -= offsetX;
	}
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y + (this->characters['H'].bearing.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 },
			{ xpos,     ypos,       0.0, 0.0 },

			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph
		x += (ch.advance /64) * scale;  // Bitshift  to get value in pixels
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

