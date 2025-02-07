#include "hxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Helix {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HX_CORE_ASSERT(windowHandle, "Window handle is null!")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HX_CORE_ASSERT(status, "Failed to initialize Glad!");

		HX_CORE_INFO("OpenGL Info:");
		HX_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HX_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HX_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}