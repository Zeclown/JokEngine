#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Jokengine
{

	// General purpsoe shader object. 
	class Shader
	{
	public:
		// Program ID
		GLuint ID;
		// Constructor
		Shader() { }
		// Sets the current shader as active
		Shader  &Use();

		// Compiles the shader from given source code and set the program ID
		void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
		// Set Uniforms
		void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
		void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
		void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
		void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
		void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
		void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
		void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
		void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
		void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

	private:
		// Prints all compilations and linking error
		void    checkCompileErrors(GLuint object, std::string type);
	};
}
#endif