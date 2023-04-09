#include "ltpch.h"
#include "Lotus/Scene/SceneCamera.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Lotus
{


	void SceneCamera::SetPerspectve(float PerspectiveFOV, float Near, float Far)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFar = Far;
		m_PerspectiveNear = Near;
		m_PerspectiveFOV = PerspectiveFOV;
	}

	void SceneCamera::SetOrthographic(float Size, float Near, float Far)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = Size;
		m_OrthographicFar = Far;
		m_OrthographicNear = Near;
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		switch (m_ProjectionType)
		{
			//使用glm::内置函数直接生成透视矩阵
		case ProjectionType::Perspective:
			m_Projection = glm::perspectiveFov(m_PerspectiveFOV, (float)width, (float)height, m_PerspectiveNear, m_PerspectiveFar);
			break;
			//经过视口变化
		case ProjectionType::Orthographic:
			float aspect = (float)width / (float)height;
			float width = m_OrthographicSize * aspect;
			float height = m_OrthographicSize;
			m_Projection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f);
			break;

		}
	}

	void SceneCamera::ReCalcaluteProjection()
	{
		switch (m_ProjectionType)
		{
			//使用glm::内置函数直接生成透视矩阵
		case ProjectionType::Perspective:
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
			break;
			//经过视口变化
		case ProjectionType::Orthographic:
			float width = m_OrthographicSize * m_AspectRatio;
			float height = m_OrthographicSize;
			m_Projection = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f);
			break;

		}
	}

}