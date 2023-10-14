#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <hg/Core/EntryPoint.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>



Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f,true)
{
}

void Sandbox2D::OnAttach()
{
	HG_PROFILE_FUNCTION();

	m_CheckboadTexture = hg::Texture2D::Create("assets/textures/1.jpg");
	
}

void Sandbox2D::OnDetach()
{
	HG_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(hg::Timestep ts)
{
	HG_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	hg::Renderer2D::ResetStats();
	{
		HG_PROFILE_SCOPE("Renderer Prep");

		hg::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		hg::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		HG_PROFILE_SCOPE("Renderer Draw");
		hg::Renderer2D::BeginScene(m_CameraController.GetCamera());
		hg::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(- 45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
		hg::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		hg::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		hg::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckboadTexture, 10.0f);
		hg::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation),m_CheckboadTexture, 20.0f);
		hg::Renderer2D::EndScene();

		hg::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y <= 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x <= 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f,0.4f,(y + 5.0f) / 10.0f,0.7f };
				hg::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
			}
		}
		hg::Renderer2D::EndScene();

	}
}

void Sandbox2D::OnImGuiRender()
{
	HG_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    auto stats = hg::Renderer2D::GetStatistics();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls : %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indeces: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
    
}

void Sandbox2D::OnEvent(hg::Event& e)
{
	m_CameraController.OnEvent(e);
}
