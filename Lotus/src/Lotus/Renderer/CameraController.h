#pragma once

#include "Lotus/Renderer/Camera.h"
#include "Lotus/Core/Timestep.h"
#include "Lotus/Core/Core.h"

#include "Lotus/Events/ApplicationEvent.h"
#include "Lotus/Events/MouseEvent.h"

#include "Lotus/Core/MouseButtonCodes.h"

namespace Lotus {

	// Camera will be be initially placed at -sqrt(zNear * zFar)
	// In orthographic mode, screen height is the height in **view space** at z=0 (word space)
	class CameraController
	{
	public:
		// aspectRatio: width / height
		CameraController(
			bool isPerspective,
			// stored for perspective
			float aspectRatio, float fovy = 45.0f, float zNear = 0.1f, float zFar = 10000.0f
		);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline Camera& GetCamera() { return *m_Camera; }
		inline const Camera& GetCamera() const { return *m_Camera; }

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::quat& rotation);
		void SetPerspective(bool isPerspective);

		inline const float GetZoomLevel() const { return m_ZoomLevel; }
		inline const float GetFovy() const { return m_Fovy; }
		inline const float GetAspectRatio() const { return m_AspectRatio; }

	private:
		glm::mat4 ComputePerspectiveProjectionMatrix();
		glm::mat4 ComputeOrthographicProjectionMatrix();
		void ResetProjectionMatrix();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		// m_MouseButtonPressed is set only in OnMouseButtonPressed (except for LT_MOUSE_BUTTON_NONE)
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
	private:
		//---------------- camera property -------------
		bool m_IsPerspective;
		float m_AspectRatio;
		float m_Fovy, m_Near, m_Far;
		float m_ZoomLevel;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		Scope<Camera> m_Camera;

		//---------------- camera speeds ---------------
		// relative to pixel
		float m_CameraTranslationSpeedXY = 0.01f;
		float m_CameraTranslationSpeedZ = 10.0f;
		float m_CameraRotationSpeedXY = 0.1f;
		// relative to scrolling
		float m_ZoomSensitivity = 0.1f, m_ZoomMin = 0.1f;
		float m_FovySensitiviy = 1.0f, m_FovyMax = 179.0f, m_FovyMin = 1.0f;

		//---------------- input states ----------------
		// Which button is currently pressed (record the first button that is pressed only)
		int m_MouseButtonPressed = LT_MOUSE_BUTTON_NONE;
		glm::vec2 m_MouseButtonPressedPosition = glm::i32vec2(0.0f, 0.0f);
	};

}
