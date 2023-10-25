#include <hg.h>

#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "hg/Renderer/Shader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer :public hg::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		// Vertex Array
			// Vertex Buffer
			// Index Buffer

		m_VertexArray = hg::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.0f,1.0f,1.0f,
			0.5f,-0.5f,0.0f,1.0f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.6f,0.0f,0.5f,1.0f,
		};
		std::shared_ptr<hg::VertexBuffer> vertexBuffer;

		vertexBuffer = hg::VertexBuffer::Create(vertices, sizeof(vertices));

		hg::BufferLayout layout = {
			{hg::ShaderDataType::Float3,"a_Position"},
			{hg::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<hg::IndexBuffer> indexBuffer;
		indexBuffer = hg::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA = hg::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f,-0.5f,0.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,0.0f,
			0.5f,0.5f,0.0f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,0.0f,1.0f
		};

		std::shared_ptr<hg::VertexBuffer> squareVB;
		squareVB = hg::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ hg::ShaderDataType::Float3,"a_Position" },
			{ hg::ShaderDataType::Float2,"a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<hg::IndexBuffer> squareIB;
		squareIB = hg::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
				}				

			)";

		std::string fragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5,1.0f);
					color = v_Color;
				}				

			)";

		// 转移所有权
		m_Shader = hg::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);

		std::string flatColorShadervertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main()
				{
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
				}				

			)";

		std::string flatColorShaderfragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				
				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color,1.0f);
				}				

			)";


		// 转移所有权
		m_flatColorShader = hg::Shader::Create("FlatColor",flatColorShadervertexSrc, flatColorShaderfragmentSrc);

		// 转移所有权
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	
		m_Texture = hg::Texture2D::Create("assets/textures/bef.jpg");
		m_logoTexture = hg::Texture2D::Create("assets/textures/1.jpg");


		std::dynamic_pointer_cast<hg::OpenGLShader>(textureShader)->bind();
		std::dynamic_pointer_cast<hg::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(hg::Timestep ts)override
	{ 
		
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		hg::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		hg::RenderCommand::Clear();

		hg::Renderer::BeginScane(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<hg::OpenGLShader>(m_flatColorShader)->bind();
		std::dynamic_pointer_cast<hg::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				hg::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);

			}
		} 

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		hg::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_logoTexture->Bind();
		hg::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// triangle
		// hg::Renderer::Submit(m_Shader, m_VertexArray);

		hg::Renderer::EndScane();
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(hg::Event& e)override
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == hg::EventType::WindowResize)
		{
			auto& re = (hg::WindowResizedEvent&)e;

			float ar = (float)re.GetWidth() / (float)re.GetHeight();

			float zoom = (float)re.GetWidth() / 1280.0f;
			m_CameraController.SetZoomLevel(zoom);
		}
	} 

private:
	hg::ShaderLibrary m_ShaderLibrary;
	hg::Ref<hg::Shader> m_Shader;
	hg::Ref<hg::VertexArray> m_VertexArray;

	hg::Ref<hg::Shader> m_flatColorShader;
	hg::Ref<hg::VertexArray> m_SquareVA;

	hg::Ref<hg::Texture2D> m_Texture,m_logoTexture;

	hg::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox :public hg::Application
{
public:
	Sandbox(const hg::ApplicationSpecification& specification)
		: hg::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());

	}

	~Sandbox()
	{

	}
};

hg::Application* hg::CreateApplication(hg::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../HGnut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}