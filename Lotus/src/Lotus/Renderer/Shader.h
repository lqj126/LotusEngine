#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Lotus {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;

	public:
		void setBool(const std::string& name, bool value)					const;
		void setInt(const std::string& name, int value)						const;
		void setFloat(const std::string& name, float value)					const;
		void setFloat2(const std::string& name, const glm::vec2& value)		const;
		void setFloat2(const std::string& name, float x, float y)				const;
		void setFloat3(const std::string& name, const glm::vec3& value)		const;
		void setFloat3(const std::string& name, float x, float y, float z)	const;
		void setFloat4(const std::string& name, const glm::vec4& value)		const;
		void setFloat4(const std::string& name, float x, float y, float z, float w);
		void setMat2(const std::string& name, const glm::mat2& mat)			const;
		void setMat3(const std::string& name, const glm::mat3& mat)			const;
		void setMat4(const std::string& name, const glm::mat4& mat)			const;
	};

}