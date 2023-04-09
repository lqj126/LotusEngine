#pragma once

#include "Lotus/Renderer/Camera.h"

namespace Lotus {


	class SceneCamera : public Camera {


	public:
		enum class ProjectionType { Perspective = 0, Orthographic };
	public:
		//设置相机属性
		void SetPerspectve(float PerspectiveFOV, float Near, float Far);
		void SetOrthographic(float Size, float Near, float Far);
		void SetViewportSize(uint32_t width, uint32_t height);
		//设置透视摄像机参数
		void SetPerspectiveVerticalFOV(float VerticalFOV) { m_PerspectiveFOV = glm::radians(VerticalFOV); ReCalcaluteProjection(); }
		float GetPerspectiveVerticalFOV() const { return glm::degrees(m_PerspectiveFOV); }
		void SetPerspectiveNearClip(float NearClip) { m_PerspectiveNear = NearClip; ReCalcaluteProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveFarClip(float FarClip) { m_PerspectiveFar = FarClip; ReCalcaluteProjection(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		//设置正交摄像机参数
		void SetOrthographicSize(float size) { m_OrthographicSize = size; ReCalcaluteProjection(); }
		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; ReCalcaluteProjection(); }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; ReCalcaluteProjection(); }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }

		void SetProjectionType(ProjectionType Type) { m_ProjectionType = Type; ReCalcaluteProjection(); }
		ProjectionType GetProjectionType() { return m_ProjectionType; }

		float GetAspectRatio() { return m_AspectRatio; }
		void SetAspectRatio(float aspectratio) { m_AspectRatio = aspectratio; ReCalcaluteProjection(); }

		void ReCalcaluteProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Perspective;

		float m_PerspectiveFOV = glm::radians(45.0f);;
		float m_PerspectiveFar = 1000.0f; float m_PerspectiveNear = 0.1f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicFar = 1.0f; float m_OrthographicNear = -1.0f;

		float m_AspectRatio;

	};
}