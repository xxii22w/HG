#pragma once

#include "hg.h"
#include "src/Panels/SceneHierarchyPanel.h"

namespace hg {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		hg::OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;


		bool m_ViewportFocuse = false,m_ViewportHovered = false;
		Ref<Texture2D> m_CheckerboardTexture;

		glm::vec2 m_ViewportSize = { 0,0 };
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}