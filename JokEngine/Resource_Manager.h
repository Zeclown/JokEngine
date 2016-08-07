#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"
#include "shader.h"
#include "SpriteSheet.h"

namespace Jokengine
{

	// A static ResourceManager class 
	// load Sprites and Shaders and store them
	// Exemple:
	//
	//  ResourceManager::LoadSprite("textures/goblin.png",GL_TRUE,"goblin")
	//  Texture2D sprite=ResourceManager::GetSprite("goblin");
	class ResourceManager
	{
	public:
		// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. Returns reference from the storage
		static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
		// Retrieves a stored shader
		static Shader   GetShader(std::string name);
		// Loads a spritesheet from a file
		static SpriteSheet LoadSpritesheet(const GLchar *file, GLboolean alpha,glm::vec2 frameSize, std::string name);
		// Retrieves a stored spritesheet
		static SpriteSheet GetSpritesheet( std::string name);
		// Loads a sprite from a file
		static Sprite LoadSprite(const GLchar *file, GLboolean alpha, std::string name);
		// Retrieves a stored sprite
		static Sprite GetSprite(std::string name);
		// de-allocates all loaded resources
		static void      Clear();
	private:
		ResourceManager() { }
		// Loads (and generates) a texture from file, returns reference from the storage
		static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
		// Retrieves a stored texture
		static Texture2D GetTexture(std::string name);
		// Resource storage
		static std::map<std::string, Shader>    shaders;
		static std::map<std::string, Texture2D> textures;
		static std::map<std::string, Sprite> sprites;
		static std::map<std::string, SpriteSheet> spriteSheets;
		// Loads and generates a shader from file
		static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
		// Loads a single texture from file
		static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
	};
}
#endif