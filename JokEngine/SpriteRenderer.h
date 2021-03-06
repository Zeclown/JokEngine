#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SpriteRenderingService.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"

//Default Sprite Rendering Service
class SpriteRenderer:public SpriteRenderingService
{
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();
	void DrawSquare(glm::vec2 center, glm::vec2 size, GLfloat angle, glm::vec3 RGBcolor=glm::vec3(1.0f,1.0f,1.0f));
	void DrawSprite(Sprite &sprite, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec4 color = glm::vec4(1.0f));
private:
	Shader shader;
	GLuint quadVAO, quadInvertedVAO;
	void initRenderData();
};

#endif