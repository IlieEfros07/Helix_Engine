#pragma once

#include "Core.h"

#include "Window.h"
#include "Helix/LayerStack.h"
#include "Events/Event.h"
#include "Helix/Events/ApplicationEvent.h"

#include "Helix/ImGui/ImGuiLayer.h"

#include "Helix/Renderer/Shader.h"

#include "Helix/Renderer/Buffer.h"

namespace Helix {
	class HELIX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}