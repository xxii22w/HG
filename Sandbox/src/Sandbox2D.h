#pragma once

#include "hg.h"

class Sandbox2D : public hg::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(hg::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(hg::Event& e) override;
private:
	hg::OrthographicCameraController m_CameraController;

	// Temp
	hg::Ref<hg::Shader> m_FlatColorShader;
	hg::Ref<hg::VertexArray> m_SquareVA;

	hg::Ref<hg::Texture2D> m_CheckboadTexture;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

};