#pragma once

struct GLFWwindow;

namespace stdio_fw
{
	class Graphics;
}
namespace stdio_fw
{
	class Application
	{
		static Application*		m_pApp;
		GLFWwindow*				m_pWindow;		
		Graphics*				m_pGraphics;
		char					m_sWindowTitle[64];

	protected:
		bool					m_isRunning;

	public:
		Application();
		virtual ~Application();

		// Init applicaion - use OpenGL 2.1
		// [in] screenW: screen width
		// [in] screenH: screen height
		// [in] title: game title
		virtual ErrorCode	init(int screenW, int screenH, const char* title);

		// Update function, must be override
		// [in] deltaTime: time between 2 frames
		virtual void		update(float deltaTime) = 0;
		virtual void		render(Graphics* g) = 0;
		virtual void		exit() = 0;

		// Get key state
		// [in] Key code
		// [out] State of key
		KeyState			getKeyState(KeyCode key);
		virtual void		onKeyProc(KeyCode key, KeyState state) = 0;
		Graphics*			getGraphics();

		void				run();

	private:
		static void glfwKeyCallbackFunc(GLFWwindow* pWindow, int key, int scancode, int action, int mods);	
	};
}
