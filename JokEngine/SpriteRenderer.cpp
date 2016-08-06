#include "SpriteRenderer.h"
#include "Game.h"
#include "Sprite.h"
namespace Jokengine
{
	SpriteRenderer::SpriteRenderer(Shader &shader)
	{
		this->shader = shader;
		this->initRenderData();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &this->quadVAO);
	}
	void SpriteRenderer::initRenderData()
	{
		// Configure VAO/VBO
		GLuint VBO;
		GLfloat vertices[] = {
			// Pos      // Tex
			-0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &this->quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void SpriteRenderer::DrawSquare(glm::vec2 position,glm::vec2 size,GLfloat rotate,glm::vec3 color)
	{
		
	}
	void SpriteRenderer::DrawSprite(Sprite &sprite, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
	{
		Texture2D &texture= *(sprite.texture);
		this->shader.Use();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1));
		model = glm::scale(model, glm::vec3(size, 0.0f));

		this->shader.SetMatrix4("model", model);
		// textured quad
		this->shader.SetVector3f("spriteColor", color);
		this->shader.SetInteger("frame",sprite.frame);
		this->shader.SetVector2f("frameSize",sprite.size);
		glActiveTexture(GL_TEXTURE0);
		texture.Bind();

		glBindVertexArray(this->quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}