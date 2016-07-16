#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"
#include "shader.h"
namespace Jokengine
{

	// A static ResourceManager class 
	// load Textures and Shaders and store them
	// Exemple:
	//
	//  ResourceManager::LoadTexture("textures/goblin.png",GL_TRUE,"goblin")
	//  Texture2D sprite=ResourceManager::GetTexture("goblin");
	class ResourceManager
	{
	public:
		// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. Returns reference from the storage
		static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
		// Retrieves a stored shader
		static Shader   GetShader(std::string name);
		// Loads (and generates) a texture from file, returns reference from the storage
		static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
		// Retrieves a stored texture
		static Texture2D GetTexture(std::string name);
		// de-allocates all loaded resources
		static void      Clear();
	private:
		ResourceManager() { }

		// Resource storage
		static std::map<std::string, Shader>    Shaders;
		static std::map<std::string, Texture2D> Textures;
		// Loads and generates a shader from file
		static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
		// Loads a single texture from file
		static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
	};
}
#endif