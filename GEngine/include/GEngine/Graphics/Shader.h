#pragma once
#include <glad/glad.h>
//#include <string>
//#include <map>
#include "Math/Math.h"




namespace GEngine::Graphic
{
	#define SET_UNIFORM_IMPL(gl_Func, tType, dType) \
	template<> void Shader::Set<tType>(const char* name, tType* data, unsigned int length) {\
										gl_Func(GetUniformLocation(name), static_cast<GLsizei>(length), (dType*)&data[0]);\
	}

	#define SET_MATRIX_IMPL(gl_Func, tType, dType) \
	template<> void Shader::Set<tType>(const char* name, tType* data, unsigned int length) {\
										gl_Func(GetUniformLocation(name), static_cast<GLsizei>(length), GL_FALSE, (dType*)&data[0][0]);\
	}

	enum ShaderType
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};


	class Shader
	{

	public:
		Shader();
		~Shader();

		//Shader class holds resource, make it non copyable and non movable
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

		void BindAttribLocation(GLuint location, const char* name) const;
		void BindFragDataLocation(GLuint location, const char* name) const;
		static const char* GetTypeString(GLenum type);

		void FindUniformLocations();
		void PrintActiveUniforms() const;
		void PrintActiveUniformBlocks() const;
		void PrintActiveAttribs() const;

		template<typename T>
		void SetUniform(const char* name, const T& data){ Set(name, (T*)(&data), 1); };

		template<typename T>
		void SetUniform(const char* name, const std::vector<T>& data) { Set(name, data.data(), data.size()); };


	private:
		GLuint GetUniformLocation(const char* name);
		void DetachAndDeleteShaderObjects()const;
		static bool FileExists(const std::string& fileName);
		static std::string GetExtension(const char* name);

		template<typename T>
		void Set(const char* name, T* arr, unsigned int length){};

		

	private:
		GLuint m_ProgramHandle{};
		bool m_Linked{};
		std::map<std::string, int> m_UniformLocations;

	};



}
