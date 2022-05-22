#include "gepch.h"
#include <Core/Window.h>
#include "Graphics/Texture.h"
#include "stb_image/stb_image.h"
#include <stb_image/stb_image_write.h>



namespace GEngine::Graphic
{

	Texture::Texture(const TextureInfo& texInfo): m_TextureInfo(texInfo)
	{

	}

	void Texture::LoadTexture(const std::string& fileName)
	{
		if (unsigned char* data = Texture::LoadPixels(fileName, m_TextureInfo.m_Width, m_TextureInfo.m_Height); data != nullptr)
		{
			glGenTextures(1, &m_TexID);
			glBindTexture(GL_TEXTURE_2D, m_TexID);

			int width = m_TextureInfo.m_Width;
			int height = m_TextureInfo.m_Height;
			GLenum& internalFormat = m_TextureInfo.m_TextureFormat.m_InternalFormat; //GL_RGBA8;
			GLenum& dataFormat = m_TextureInfo.m_TextureFormat.m_DataFormat; //GL_RGBA;

			int channel = m_TextureInfo.m_Channels;
			bool isGamma = m_TextureInfo.b_GammaCorrection;

			switch (channel)
			{
			case 1:  internalFormat = GL_R8;  dataFormat = GL_RED; break;
			case 3:  internalFormat = isGamma ? GL_SRGB8 : GL_RGB8; dataFormat = GL_RGB; break;
			case 4:  internalFormat = isGamma ? GL_SRGB8_ALPHA8 : GL_RGBA8; dataFormat = GL_RGBA; break;
			default: break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TextureInfo.m_TextureSpec.m_WrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TextureInfo.m_TextureSpec.m_WrapT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);

			//check if hardware support anisotropic filtering
			if (GLAD_GL_EXT_texture_filter_anisotropic)
			{
				GLfloat largest;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);

				//activate anisotropic filtering
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
			}



			DeletePixels(data);

		}
	}


	void Texture::LoadHdrTexture(const std::string& fileName)
	{
		stbi_set_flip_vertically_on_load(true);

		int& width = m_TextureInfo.m_Width;
		int& height = m_TextureInfo.m_Height;
		int& channel = m_TextureInfo.m_Channels;
		int texTarget = m_TextureInfo.m_TextureSpec.m_TexTarget;

		if (float* data = stbi_loadf(fileName.c_str(), &width, &height, &channel, 0); data)
		{
			glGenTextures(1, &m_TexID);
			glBindTexture(texTarget, m_TexID);

			glTexStorage2D(texTarget, 1, GL_RGB16F, width, height);
			glTexSubImage2D(texTarget, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, data);

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, data);

			//glGenerateMipmap(GL_TEXTURE_2D);

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TextureInfo.m_TextureSpec.m_WrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TextureInfo.m_TextureSpec.m_WrapT);

			//check if hardware support anisotropic filtering
			if (GLAD_GL_EXT_texture_filter_anisotropic)
			{
				GLfloat largest;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);

				//activate anisotropic filtering
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);


			stbi_image_free(data);

		};

	}


	void Texture::LoadCubeMap(const std::string& baseName, const std::string& extension)
	{

		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TexID);

		const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
		//GLint w, h;

		// Load the first one to get width/height
		std::string texName = baseName + "/" + suffixes[0] + extension;
		GLubyte* data = Texture::LoadPixels(texName, m_TextureInfo.m_Width, m_TextureInfo.m_Height, false);

		GLenum internalFormat = GL_RGBA8;
		GLenum dataFormat = GL_RGBA;

		// Allocate immutable storage for the whole cube map texture
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, internalFormat, m_TextureInfo.m_Width, m_TextureInfo.m_Height);
		glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, m_TextureInfo.m_Width, m_TextureInfo.m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		// Load the other 5 cube-map faces
		for (int i = 1; i < 6; i++) {
			texName = baseName + "/" + suffixes[i] + extension;
			data = Texture::LoadPixels(texName, m_TextureInfo.m_Width, m_TextureInfo.m_Height, false);
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, m_TextureInfo.m_Width, m_TextureInfo.m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);

		//check if hardware support anisotropic filtering
		if (GLAD_GL_EXT_texture_filter_anisotropic)
		{
			GLfloat largest;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);

			//activate anisotropic filtering
			glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_TextureInfo.m_TextureSpec.m_WrapS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_TextureInfo.m_TextureSpec.m_WrapT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, m_TextureInfo.m_TextureSpec.m_WrapR);


	}

	void Texture::LoadHdrCubeMap(const std::string& baseName)
	{

		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TexID);

		const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
		//GLint w, h;

		// Load the first one to get width/height
		std::string texName = baseName + "/" + suffixes[0] + ".hdr";
		float* data = stbi_loadf(texName.c_str(), &m_TextureInfo.m_Width, &m_TextureInfo.m_Height, &m_TextureInfo.m_Channels, 0);

		// Allocate immutable storage for the whole cube map texture
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGB32F, m_TextureInfo.m_Width, m_TextureInfo.m_Height);
		glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, m_TextureInfo.m_Width, m_TextureInfo.m_Height, GL_RGB, GL_FLOAT, data);
		stbi_image_free(data);

		// Load the other 5 cube-map faces
		for (int i = 1; i < 6; i++)
		{
			texName = baseName + "/" + suffixes[i] + ".hdr";
			data = stbi_loadf(texName.c_str(), &m_TextureInfo.m_Width, &m_TextureInfo.m_Height, &m_TextureInfo.m_Channels, 0);
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, m_TextureInfo.m_Width, m_TextureInfo.m_Height, GL_RGB, GL_FLOAT, data);
			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}


	void Texture::Bind() const
	{
		glBindTexture(m_TextureInfo.m_TextureSpec.m_TexTarget, m_TexID);
	}



	void Texture::CreateFromSurface(SDL_Surface* surface)
	{
		m_TextureInfo.m_Width = surface->w;
		m_TextureInfo.m_Height = surface->h;

		// Generate a GL texture
		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TextureInfo.m_Width, m_TextureInfo.m_Height, 0, GL_BGRA,
			GL_UNSIGNED_BYTE, surface->pixels);

		// Use linear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}



	void Texture::CreateForRendering(const TextureInfo& texInfo)
	{
		m_TextureInfo = texInfo;
		glGenTextures(1, &m_TexID);

		m_TextureInfo.m_TextureSpec.m_TexTarget = m_TextureInfo.b_CubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
		Bind();

		// Set the image width/height with null initial data
		if (!texInfo.b_CubeMap)
		{

			glTexImage2D(m_TextureInfo.m_TextureSpec.m_TexTarget, 0, texInfo.m_TextureFormat.m_InternalFormat, m_TextureInfo.m_Width, m_TextureInfo.m_Height, 0, texInfo.m_TextureFormat.m_DataFormat,
				texInfo.m_TextureFormat.m_DataType, nullptr);


			//check if hardware support anisotropic filtering
			if (GLAD_GL_EXT_texture_filter_anisotropic)
			{
				GLfloat largest;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);

				//activate anisotropic filtering
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
			}

			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_WRAP_S, m_TextureInfo.m_TextureSpec.m_WrapS);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_WRAP_T, m_TextureInfo.m_TextureSpec.m_WrapT);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);
		}

		else
		{
			for (unsigned int i = 0; i < 6; ++i)
			{
				//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_TextureInfo.m_TextureFormat.m_InternalFormat,
					m_TextureInfo.m_Width, m_TextureInfo.m_Height, 0, m_TextureInfo.m_TextureFormat.m_DataFormat,
					m_TextureInfo.m_TextureFormat.m_DataType, nullptr);
			}


			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_WRAP_S, m_TextureInfo.m_TextureSpec.m_WrapS);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_WRAP_T, m_TextureInfo.m_TextureSpec.m_WrapT);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_WRAP_R, m_TextureInfo.m_TextureSpec.m_WrapR);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_MIN_FILTER, m_TextureInfo.m_TextureSpec.m_MinFilter);
			glTexParameteri(m_TextureInfo.m_TextureSpec.m_TexTarget, GL_TEXTURE_MAG_FILTER, m_TextureInfo.m_TextureSpec.m_MagFilter);

			if (texInfo.b_GenerateMipmap)
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}


	}


	void Texture::WritePixels(Window* focusWindow, const std::string& fileName, int channels)
	{
		
		int width = focusWindow->GetScreenWidth();
		int height = focusWindow->GetScreenHeight();


		uint8_t* ptr = (uint8_t*)malloc(width * height * channels);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		stbi_write_png(fileName.c_str(), width, height, channels, ptr, 0);
		free(ptr);

	}


	unsigned char* Texture::LoadPixels(const std::string& fileName, int& width, int& height, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &m_TextureInfo.m_Channels, 0);
		return data;
	}


	void Texture::DeletePixels(unsigned char* data)
	{
		stbi_image_free(data);
	}

}