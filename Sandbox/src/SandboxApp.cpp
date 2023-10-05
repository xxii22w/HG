#include <hg.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "hg/Renderer/Shader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer :public hg::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		// Vertex Array
			// Vertex Buffer
			// Index Buffer

		m_VertexArray.reset(hg::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.0f,1.0f,1.0f,
			0.5f,-0.5f,0.0f,1.0f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.6f,0.0f,0.5f,1.0f,
		};
		std::shared_ptr<hg::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(hg::VertexBuffer::Create(vertices, sizeof(vertices)));

		hg::BufferLayout layout = {
			{hg::ShaderDataType::Float3,"a_Position"},
			{hg::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<hg::IndexBuffer> indexBuffer;
		indexBuffer.reset(hg::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(hg::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f,-0.5f,0.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,0.0f,
			0.5f,0.5f,0.0f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,0.0f,1.0f
		};

		std::shared_ptr<hg::VertexBuffer> squareVB;
		squareVB.reset(hg::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ hg::ShaderDataType::Float3,"a_Position" },
			{ hg::ShaderDataType::Float2,"a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<hg::IndexBuffer> squareIB;
		squareIB.reset(hg::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		if (hg::Input::IsKeyPressed(HG_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (hg::Input::IsKeyPressed(HG_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (hg::Input::IsKeyPressed(HG_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (hg::Input::IsKeyPressed(HG_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (hg::Input::IsKeyPressed(HG_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (hg::Input::IsKeyPressed(HG_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		
		hg::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		hg::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		hg::Renderer::BeginScane(m_Camera);

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

	void OnEvent(hg::Event& event)override
	{

	} 

private:
	hg::ShaderLibrary m_ShaderLibrary;
	hg::Ref<hg::Shader> m_Shader;
	hg::Ref<hg::VertexArray> m_VertexArray;

	hg::Ref<hg::Shader> m_flatColorShader;
	hg::Ref<hg::VertexArray> m_SquareVA;

	hg::Ref<hg::Texture2D> m_Texture,m_logoTexture;

	hg::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMovepeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox :public hg::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}
	~Sandbox()
	{

	}
};

hg::Application* hg::CreateApplication()
{
	return new Sandbox();
}