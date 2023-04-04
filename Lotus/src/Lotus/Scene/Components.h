#pragma once
#include "Lotus/Renderer/Model.h"
#include <glm/glm.hpp>

namespace Lotus {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct ModelComponent
	{
		Lotus::Ref<Lotus::Model> Model = Lotus::CreateRef<Lotus::Model>("H:/Dev/Lotus/Sandbox/assets/models/nanosuit/nanosuit.obj");

		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent(const Lotus::Ref<Lotus::Model> model)
			: Model(model) {}
	};

}