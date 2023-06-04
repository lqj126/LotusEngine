#pragma once
#include "ltpch.h"
#include "Shader.h"
#include "Texture.h"
#include "CameraController.h"
#include"Lotus/Renderer/FrameBuffer.h"
namespace Lotus
{
	void renderQuad();
	void renderCube();
	void renderSphere();



	class IBLRenderer
	{
	public:
		~IBLRenderer() {};

		void setupIBL(CameraController& camera, FramebufferSpecification Specification);
		void renderLoop(CameraController& camera, FramebufferSpecification Specification);
	private:
		unsigned int captureFBO;
		unsigned int captureRBO;

		unsigned int irradianceMap;
		int width, height, nrComponents;
		float* data = nullptr;
		unsigned int hdrTexture;
		// lights
		glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f),
		};
		glm::vec3 lightColors[4] = {
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f)
		};
	private:
		unsigned int prefilterMap;
		unsigned int brdfLUTTexture;
		unsigned int envCubemap;
		// settings
		unsigned int SCR_WIDTH = 1280;
		unsigned int SCR_HEIGHT = 720;

		// camera


		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;

		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		ShaderLibrary m_ShaderLibrary;
		Ref<Shader> IBLShader;
		Ref<Shader> pbrShader;
		Ref<Shader> equirectangularToCubemapShader;
		Ref<Shader> irradianceShader;
		Ref<Shader> prefilterShader;
		Ref<Shader> brdfShader;
		Ref<Shader> backgroundShader;

#ifndef true
		// rusted iron
		Ref<Texture2D>ironAlbedoMap;
		Ref<Texture2D>ironNormalMap;
		Ref<Texture2D>ironMetallicMap;
		Ref<Texture2D>ironRoughnessMap;
		Ref<Texture2D>ironAOMap;

		// gold
		Ref<Texture2D>goldAlbedoMap;
		Ref<Texture2D>goldNormalMap;
		Ref<Texture2D>goldMetallicMap;
		Ref<Texture2D>goldRoughnessMap;
		Ref<Texture2D>goldAOMap;

		// copper
		Ref<Texture2D>grassAlbedoMap;
		Ref<Texture2D>grassNormalMap;
		Ref<Texture2D>grassMetallicMap;
		Ref<Texture2D>grassRoughnessMap;
		Ref<Texture2D>grassAOMap;

		// spaceship
		Ref<Texture2D>plasticAlbedoMap;
		Ref<Texture2D>plasticNormalMap;
		Ref<Texture2D>plasticMetallicMap;
		Ref<Texture2D>plasticRoughnessMap;
		Ref<Texture2D>plasticAOMap;

		// wall
		Ref<Texture2D>wallAlbedoMap;
		Ref<Texture2D>wallNormalMap;
		Ref<Texture2D>wallMetallicMap;
		Ref<Texture2D>wallRoughnessMap;
		Ref<Texture2D>wallAOMap;
#endif
	};
}