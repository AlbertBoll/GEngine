#pragma once

#include <map>
#include "Math/Math.h"


namespace GEngine::Asset
{
	//Helper macro to set vector uniform 
	#define SET_UNIFORM_IMPL(gl_Func, tType, dType) \
	template<> void Shader::Set<tType>(const char* name, tType* data, unsigned int length) {\
										gl_Func(GetUniformLocation(name), static_cast<int>(length), (dType*)&data[0]);\
	}


	//Helper macro to set matrix uniform  
	#define SET_MATRIX_IMPL(gl_Func, tType, dType) \
	template<> void Shader::Set<tType>(const char* name, tType* data, unsigned int length) {\
										gl_Func(GetUniformLocation(name), static_cast<int>(length), false, (dType*)&data[0][0]);\
	}

	enum ShaderType
	{
		VERTEX = 0x8B31,
		FRAGMENT = 0x8B30,
		GEOMETRY = 0x8DD9,
		TESS_CONTROL = 0x8E88,
		TESS_EVALUATION = 0x8E87,
		COMPUTE = 0x91B9
	};


	class Shader
	{

	public:
		Shader();
		~Shader();

		//Shader class holds resource, make it non copyable
		NONCOPYABLE(Shader);
		Shader(Shader&& other)noexcept;
		Shader& operator=(Shader&& other)noexcept;

		void CompileShader(const char* fileName);
		void CompileShader(const char* fileName, ShaderType type);
		void CompileShader(const std::string& source, ShaderType type, const char* fileName);

		void Link();
		void Validate() const;
		void Bind() const;

		[[nodiscard]] int GetHandle() const;
		[[nodiscard]] bool IsLinked() const;

		void Destroy();
		void BindAttribLocation(unsigned int location, const char* name) const;
		void BindFragDataLocation(unsigned int location, const char* name) const;
		static const char* GetTypeString(unsigned int type);

		//void BindTextureUniform(int )

		void FindUniformLocations();
		void PrintActiveUniforms() const;
		void PrintActiveUniformBlocks() const;
		void PrintActiveAttribs() const;
		void BindTextureUniform(unsigned int TexID, unsigned int TexUnit, unsigned int TexTarget);

		template<typename T>
		void SetUniform(const char* name, const T& data){ Set(name, (T*)(&data), 1); };

		template<typename T>
		void SetUniform(const char* name, const std::vector<T>& data) { Set(name, data.data(), data.size()); };


	private:
		unsigned int GetUniformLocation(const char* name);
		void DetachAndDeleteShaderObjects()const;
		static bool FileExists(const std::string& fileName);
		static std::string GetExtension(const char* name);

		template<typename T>
		void Set(const char* name, T* arr, unsigned int length){};

		

	private:
		unsigned int m_ProgramHandle{};
		bool m_Linked{};
		std::map<std::string, int> m_UniformLocations;

	};



}
