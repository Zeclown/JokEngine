#include"InputReader.h"
namespace Jokengine
{
	InputReader *InputReader::instance_ = 0;
	void InputReader::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) // this method is specified as glfw key callback
	{
		//here we access the instance via the singleton pattern and forward the callback to the instance method
		InputReader::instance().ProcessKeyInput(window, key, action, mods);
	}
	void InputReader::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		InputReader::instance().ProcessKeyInput(window, button, action, mods);
	}

	InputReader::InputReader()
	{
		keys = keyBuffer1;
		nextKeys = keyBuffer2;
		
		for (int i = 0; i < 2024; i++)
		{
			keys[i] = E_KEYSTATE::KEYNONE;
			nextKeys[i] = E_KEYSTATE::KEYNONE;
		}
	}

	void InputReader::ProcessKeyInput(GLFWwindow* window, int key, int action, int mods)
	{

		if (action == GLFW_PRESS && nextKeys[key] !=E_KEYSTATE::KEYHELD )
		{
			
			nextKeys[key] = E_KEYSTATE::KEY_DOWN;
			
		}
		else if (action == GLFW_RELEASE)
		{
			nextKeys[key] = E_KEYSTATE::KEY_UP;
		}	
	}
	std::vector<GLfloat> InputReader::GetMouseAxis()
	{
		
		return { deltaXMouse ,deltaYMouse };
	}
	std::vector<GLfloat> InputReader::GetJoystickAxis(int joystick)
	{
		return {};
	}
	void InputReader::ProcessMouseMovement(GLFWwindow* window, double xpos, double ypos)
	{
		GLfloat xoffset = xpos - lastXMouse;
		GLfloat yoffset = lastYMouse - ypos; // Reversed since y-coordinates range from bottom to top
		lastXMouse = xpos;
		lastYMouse = ypos;
		deltaXMouse = xoffset*sensitivity;
		deltaYMouse = yoffset*sensitivity;
	}
	void InputReader::UpdateInput()
	{
	
		std::swap(keys, nextKeys);

		for (int i = 0; i < 2024; i++) {
			
			if (keys[i] == E_KEYSTATE::KEY_UP)
			{
				nextKeys[i] = E_KEYSTATE::KEYNONE;
			}
			else if (keys[i] == E_KEYSTATE::KEY_DOWN)
			{
				nextKeys[i] = E_KEYSTATE::KEYHELD;
			}
			else if (keys[i] == E_KEYSTATE::KEYHELD)
			{
				nextKeys[i] = E_KEYSTATE::KEYHELD;
			}
		}
		
	}
	GLboolean InputReader::isButtonUp(GLint key)
	{
		return keys[key] == E_KEYSTATE::KEY_UP;
	}
	GLboolean InputReader::isButtonDown(GLint key)
	{
		return keys[key] == E_KEYSTATE::KEY_DOWN;
	}
	GLboolean InputReader::isButton(GLint key)
	{
		return keys[key] == E_KEYSTATE::KEYHELD;
	}
}