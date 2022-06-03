#include "gepch.h"
#include <Assets/Shaders/Shader.h>
#include "Material/Material.h"


namespace GEngine
{
	Material::Material(const std::string& vertexFileName, const std::string& fragFileName)
	{

	}

	GLuint Material::GetShaderRef() const
	{
		return m_Shader->GetHandle();
	}

	void Material::UseProgram() const
	{
		m_Shader->Bind();
	}

	Material::Material(Material&& other)noexcept
	{
		m_Setting = other.m_Setting;
		m_Shader = std::move(other.m_Shader);
		
		other.m_Shader = nullptr;
	}
	Material& Material::operator=(Material&& other) noexcept
	{
		if (this != &other)
		{
			m_Shader = other.m_Shader;
			other.m_Shader = nullptr;
			m_Setting = other.m_Setting;
		}

		return *this;
	}
}