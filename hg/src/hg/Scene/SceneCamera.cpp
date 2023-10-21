#include "hgpch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace hg {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetPrespective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::perspective;
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		HG_CORE_ASSERT(width > 0 && height > 0);
		m_AspectRadio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{

		if (m_ProjectionType == ProjectionType::perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRadio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRadio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRadio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			m_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}

	}
}
