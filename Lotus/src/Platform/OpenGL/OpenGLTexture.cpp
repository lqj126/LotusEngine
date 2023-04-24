#include "ltpch.h"
#include "OpenGLTexture.h"
#include "Lotus/Core/Constants.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Lotus {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
		: m_Path(""), m_Width(width), m_Height(height), m_Channels(4)
	{
		Init();
		if (data)
		{
			SetData(data, m_Width * m_Height * m_Channels);
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		std::string oldStr = "\\";
		std::string newStr = "/";
		std::string P = path;
		size_t pos = P.find(oldStr);
		while (pos != std::string::npos) {
			P.replace(pos, oldStr.length(), newStr);
			pos = P.find(oldStr, pos + newStr.length());
		}

		stbi_uc* data = stbi_load(P.c_str(), &width, &height, &channels, 0);
		LT_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		Init();

		SetData(data, m_Width * m_Height * m_Channels);
		//glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		LT_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetTexWrapS(int param)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GetGLParam(param));
	}

	void OpenGLTexture2D::SetTexWrapT(int param)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GetGLParam(param));
	}

	void OpenGLTexture2D::Init()
	{
		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		else if (m_Channels == 1)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RED;
		}

		LT_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	int OpenGLTexture2D::GetGLParam(int param) const
	{
		switch (param)
		{
		case LT_REPEAT: return GL_REPEAT;
		case LT_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
		case LT_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
		case LT_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
		case LT_NEAREST: return GL_NEAREST;
		case LT_LINEAR: return GL_LINEAR;
		case LT_NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
		case LT_LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
		case LT_NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
		case LT_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
		}
		LT_CORE_ASSERT(0, "Unsupported Param");
		return 0;
	}

}
