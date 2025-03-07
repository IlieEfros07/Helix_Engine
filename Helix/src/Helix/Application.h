#pragma once

#include "Core.h"

#include "Window.h"
#include "Helix/LayerStack.h"
#include "Events/Event.h"
#include "Helix/Events/ApplicationEvent.h"
#include "Helix/Core/Timestep.h"

#include "Helix/ImGui/ImGuiLayer.h"



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
	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;





	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}