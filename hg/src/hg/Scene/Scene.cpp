#include "hgpch.h"
#include "Scene.h"
#include "Components.h"
#include "hg/Renderer/Renderer2D.h"
#include <glm/glm.hpp>
#include "Entity.h"

namespace hg {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry,entt::entity entity)
	{

	}

	Scene::Scene()																				// 网格组件
	{

#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();												// 创建一个实体
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));						// 向注册表添加一个变换组件
		
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();			// 事务链接，每次我们添加一个变换组件的时候，都会调用这个函数


		if (m_Registry.all_of<TransformComponent>(entity))										// 判断这个实体是否在注册表中
		{
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);			// 获取 TransformComponent实体的引用
		}

		auto view = m_Registry.view<TransformComponent>();										// 创建一个TransformComponent类型实体的视图
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);			// 将MeshComponent类型的组件放入一个组
		for (auto entity : group)
		{
			auto[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}
		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
}