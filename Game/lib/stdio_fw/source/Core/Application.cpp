#include "stdio_fw.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Core\Application.h"
#include "Video\Graphics.h"

namespace stdio_fw
{
	Application* Application::m_pApp = nullptr;
	Application::Application() :m_pWindow(nullptr), m_isRunning(false)
	{
		m_pApp = this;
	}

	Application::~Application()
	{
		SAFE_DEL(m_pGraphics);
	}

	ErrorCode Application::init(int screenW, int screenH, const char* title)
	{
		/* Initialize the library */
		if (!glfwInit())
			return ErrorCode::ERR_INVALID_OPERATION;

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		/* Use OpenGL 2.1 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

		
		/* Compute window rectangle dimensions based on requested client area dimensions. */
		RECT R = { 0, 0, screenW, screenH };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		/* Create a windowed mode window and its OpenGL context */
		m_pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_pWindow)
		{
			SHOW_ERROR_MSG("Failed to open GLFW window\n");
			glfwTerminate();
			return ErrorCode::ERR_INVALID_OPERATION;
		}
		glfwMakeContextCurrent(m_pWindow);		
		glfwSetKeyCallback(m_pWindow, glfwKeyCallbackFunc);

		/* Initialize GLEW */
		if (glewInit() != GLEW_OK) {
			SHOW_ERROR_MSG("Failed to initialize GLEW\n");
			return ErrorCode::ERR_INVALID_OPERATION;
		}

		/* Init graphics system */
		//Font::initFontLib();
		m_pGraphics = new Graphics();
		m_pGraphics->initGraphics(screenW, screenH);

		strcpy_s(m_sWindowTitle, title);
		
		return ErrorCode::ERR_NO_ERROR;
	}

	KeyState Application::getKeyState(KeyCode key)
	{
		return glfwGetKey(m_pWindow, key) == GLFW_PRESS ? KeyState::KEY_PRESSED : KeyState::KEY_RELEASED;
	}

	Graphics* Application::getGraphics()
	{
		return m_pGraphics;
	}


	void Application::run()
	{
		DWORD lastTime = GetTickCount();
		m_isRunning = true;

		while (!glfwWindowShouldClose(m_pWindow) && m_isRunning == true)
		{
			DWORD curTime = GetTickCount();
			float deltaTime = static_cast<float>(curTime - lastTime);
			lastTime = curTime;

			update(deltaTime);
			render(m_pGraphics);

			// Set new window title
			char title[128];
			sprintf_s(title, 128, "%s - Frame time: %.2fms", m_sWindowTitle, deltaTime);
			glfwSetWindowTitle(m_pWindow, title);

			glfwSwapBuffers(m_pWindow);
			glfwPollEvents();
		}

		exit();
		glfwTerminate();
	}

	void Application::glfwKeyCallbackFunc(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
	{
		m_pApp->onKeyProc((KeyCode)key, (KeyState)action);
	}
}

