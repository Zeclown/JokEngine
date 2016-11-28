#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <GL/glew.h>
#include <iostream>
#include <GLFW\glfw3.h>
#include<glm\vec2.hpp>
#include<vector>
#include<array>
#include<boost\signals2.hpp>
enum E_KEYSTATE {
	KEY_UP,KEY_DOWN,KEYHELD,KEYNONE
};
// A Singleton InputReader class that stores currently pressed keys
// 
// Exemple:
//InputReader input=InputReader::instance()
//if(input.isButtonDown(GLFW_KEY_E))
//	DoSomethingAwesome();
//

class InputReader
{
public:
	static InputReader& instance()
	{
		if (!instance_)
			instance_ = new InputReader;
		return *instance_;
	}
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods); // this method is specified as glfw key callback
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);// this method is specified as glfw mouse button callback
	static void CharmodsCallback(GLFWwindow* window, unsigned int codepoint, int mods);//this method is specified as glfw text input callback
	std::vector<GLfloat> GetMouseAxis();
	std::vector<GLfloat> GetJoystickAxis(int joystick);	
	//Has the button just been released -1 for any key
	GLboolean isButtonUp(GLint key);
	//Has the button just been pressed -1 for any key
	GLboolean isButtonDown(GLint key);
	//Is the button held down -1 for any key
	GLboolean isButton(GLint key);

	
	void ProcessKeyInput(GLFWwindow* window, int key, int action, int mods);
	void ProcessMouseMovement(GLFWwindow* window, double xpos, double ypos);
	void UpdateInput();

	static boost::signals2::signal<void(unsigned int)> OnTextInput;

private:

	E_KEYSTATE *keys;
	E_KEYSTATE *nextKeys;
	E_KEYSTATE keyBuffer1[2024];
	E_KEYSTATE keyBuffer2[2024];
	GLfloat lastXMouse = 400, lastYMouse = 300;
	GLfloat sensitivity = 0.05f;
	GLfloat deltaXMouse = 0, deltaYMouse = 0;
	static InputReader *instance_;
	InputReader();

};



#endif