#pragma once

#include "Core.h"

#include "Window.h"
#include "Helix/LayerStack.h"
#include "Events/Event.h"
#include "Helix/Events/ApplicationEvent.h"

#include "Helix/ImGui/ImGuiLayer.h"
#include "Helix/Renderer/Shader.h"
#include "Helix/Renderer/Buffer.h"
#include "Helix/Renderer/VertexArray.h"
#include "Helix/Renderer/OrthographicCamera.h"


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


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;


		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;


	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}