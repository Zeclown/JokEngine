
#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

namespace Jokengine
{
	std::map<std::string, Texture2D>    ResourceManager::textures;
	std::map<std::string, Shader>       ResourceManager::shaders;
	std::map<std::string, Sprite>       ResourceManager::sprites;
	std::map<std::string, SpriteSheet>       ResourceManager::spriteSheets;

	Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
	{
		shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return shaders[name];
	}
	Shader ResourceManager::GetShader(std::string name)
	{
		return shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
	{
		textures[name] = loadTextureFromFile(file, alpha);
		return textures[name];
	}

	Texture2D ResourceManager::GetTexture(std::string name)
	{
		return textures[name];
	}
	SpriteSheet ResourceManager::LoadSpritesheet(const GLchar *file, GLboolean alpha, glm::vec2 frameSize, std::string name)
	{
		ResourceManager::LoadTexture(file, alpha, name);
		spriteSheets[name]= SpriteSheet(&textures[name], frameSize);
		return spriteSheets[name];
	}
	SpriteSheet ResourceManager::GetSpritesheet(std::string name)
	{
		return spriteSheets[name];
	}
	Sprite ResourceManager::LoadSprite(const GLchar *file, GLboolean alpha, std::string name)
	{
		ResourceManager::LoadTexture(file, alpha, name);
		sprites[name] = Sprite(&textures[name]);
		return sprites[name];
	}
	Sprite ResourceManager::GetSprite(std::string name)
	{
		return sprites[name];
	}
	void ResourceManager::Clear()
	{
		// delete shaders	
		for (auto iter : shaders)
			glDeleteProgram(iter.second.ID);
		// delete textures
		for (auto iter : textures)
			glDeleteTextures(1, &iter.second.ID);

	}

	Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// If geometry shader path is present, also load a geometry shader
			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files " << std::endl;
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();
		const GLchar *gShaderCode = geometryCode.c_str();
		// 2. Now create shader object from source code
		Shader shader;
		shader.Compile(vShaderCode, fShaderCode, gShaderFile);
		return shader;
	}

	Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
	{
		// Create Texture object
		Texture2D texture;
		if (alpha)
		{
			texture.Internal_Format = GL_RGBA;
			texture.Image_Format = GL_RGBA;
		}
		// Load image
		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
		// Now generate texture
		texture.Generate(width, height, image);
		// And finally free image data
		SOIL_free_image_data(image);
		return texture;
	}
}