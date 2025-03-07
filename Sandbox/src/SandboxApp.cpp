#include <Helix.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class ExampleLayer : public Helix::Layer {
public:
	ExampleLayer() : Layer("Example"),  m_CameraController(1280.0f/720.0f,true){

		m_VertexArray.reset(Helix::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Helix::Ref<Helix::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Helix::VertexBuffer::Create(vertices, sizeof(vertices)));
		Helix::BufferLayout layout = {
			{ Helix::ShaderDataType::Float3, "a_Position" },
			{ Helix::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Helix::Ref<Helix::IndexBuffer> indexBuffer;
		indexBuffer.reset(Helix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Helix::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Helix::Ref<Helix::VertexBuffer> squareVB;
		squareVB.reset(Helix::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Helix::BufferLayout squareLayout = {
			{ Helix::ShaderDataType::Float3, "a_Position" },
			{ Helix::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Helix::Ref<Helix::IndexBuffer> squareIB;
		squareIB.reset(Helix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader=Helix::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader=Helix::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);



		auto textureShdaer = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Helix::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Helix::Texture2D::Create("assets/logo/Helix_Logo.png");
		std::dynamic_pointer_cast<Helix::OpenGLShader>(textureShdaer)->Bind();
		std::dynamic_pointer_cast<Helix::OpenGLShader>(textureShdaer)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(Helix::Timestep ts) override {


		m_CameraController.OnUpdate(ts);


		Helix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Helix::RenderCommand::Clear();


		Helix::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Helix::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Helix::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Helix::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}


		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Helix::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		Helix::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Helix::Renderer::Submit(m_Shader, m_VertexArray);

		Helix::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color",glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Helix::Event& e) override {
		m_CameraController.OnEvent(e);
	}


private:

	Helix::ShaderLibrary m_ShaderLibrary;
	Helix::Ref<Helix::Shader> m_Shader;
	Helix::Ref<Helix::VertexArray> m_VertexArray;

	Helix::Ref<Helix::Shader> m_FlatColorShader;
	Helix::Ref<Helix::VertexArray> m_SquareVA;

	Helix::Ref<Helix::Texture2D>m_Texture, m_LogoTexture;

	Helix::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };






	

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
