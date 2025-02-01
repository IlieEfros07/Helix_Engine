#include <Helix.h>

#include "imgui.h"


class ExampleLayer : public Helix::Layer {
public: 
	ExampleLayer() : Layer("Example") {

	}
	void OnUpdate() override {
		//HX_INFO("ExampleLayer::Update");
		if (Helix::Input::IsKeyPressed(HX_KEY_TAB))
			HX_TRACE("Tab key is pressed (poll)!");
	}


	void OnImGuiRender() override {
		ImGui::Begin("test");
		ImGui::Text("HelloWorld");
		ImGui::End();
	}


	void OnEvent(Helix::Event& event) override {
		//HX_TRACE("{0}", event);
		if (event.GetEventType() == Helix::EventType::KeyPressed) {
			Helix::KeyPressedEvent& e = (Helix::KeyPressedEvent&)event;
			HX_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};




class Sandbox : public Helix::Application {
public:
	Sandbox(){
		PushLayer(new ExampleLayer());

	}
	~Sandbox() {

	}
};
Helix::Application* Helix::CreateApplication() {
	return new Sandbox();
}

