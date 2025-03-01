#include <Helix.h>

#include "imgui.h"

class ExampleLayer : public Helix::Layer {
public:
	ExampleLayer() : Layer("Example"),  m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f){


		m_VertexArray.reset(Helix::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.2f,0.8f,1.0f,
			0.5f, -0.5f,0.0f,0.2f,0.3f,0.8f,1.0f,
			0.0f, 0.5f,0.0f,0.8f,0.8f,0.2f,1.0f
		};

		std::shared_ptr<Helix::VertexBuffer>vertexBuffer;
		vertexBuffer.reset(Helix::VertexBuffer::Create(vertices, sizeof(vertices)));
		Helix::BufferLayout layout = {
			{Helix::ShaderDataType::Float3,"a_Position"},
			{Helix::ShaderDataType::Float4,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Helix::IndexBuffer>indexBuffer;
		indexBuffer.reset(Helix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string triangleShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
	
			uniform mat4 u_ViewProjection;		

			out vec4 v_Color;
    
			void main() {
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string triangleShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
    
			in vec4 v_Color;
    
			void main() {
				color = v_Color;
			}
		)";

		m_Shader.reset(new Helix::Shader(triangleShaderVertexSrc, triangleShaderFragmentSrc));



		m_SquareVA.reset(Helix::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Helix::VertexBuffer> squareVB;
		squareVB.reset(Helix::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Helix::BufferLayout squareLayout = {
			{ Helix::ShaderDataType::Float3, "a_Position" }
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Helix::IndexBuffer> squareIB;
		squareIB.reset(Helix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
	
			uniform mat4 u_ViewProjection;		

			out vec3 v_Position;
			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Helix::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}
	void OnUpdate(Helix::Timestep ts) override {




		if (Helix::Input::IsKeyPressed(HX_KEY_LEFT)) 
			m_CameraPosition.x -= m_CameraMoveSpeed*ts;
		
		else if (Helix::Input::IsKeyPressed(HX_KEY_RIGHT)) 
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		if (Helix::Input::IsKeyPressed(HX_KEY_UP)) 
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		
		else if (Helix::Input::IsKeyPressed(HX_KEY_DOWN)) 
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Helix::Input::IsKeyPressed(HX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Helix::Input::IsKeyPressed(HX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;





		Helix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Helix::RenderCommand::Clear();

		

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);


		Helix::Renderer::BeginScene(m_Camera);

		Helix::Renderer::Submit(m_BlueShader, m_SquareVA);
		Helix::Renderer::Submit(m_Shader, m_VertexArray);

		Helix::Renderer::EndScene();
	}

	void OnImGuiRender() override {

	}

	void OnEvent(Helix::Event& event) override {

	}


private:
	std::shared_ptr<Helix::Shader> m_Shader;
	std::shared_ptr<Helix::VertexArray> m_VertexArray;


	std::shared_ptr<Helix::Shader> m_BlueShader;
	std::shared_ptr<Helix::VertexArray> m_SquareVA;

	Helix::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed =5.0f;

	float m_CameraRotationSpeed =180.0f;
	float m_CameraRotation = 0.0f;


};

class Sandbox : public Helix::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};
Helix::Application* Helix::CreateApplication() {
	return new Sandbox();
}