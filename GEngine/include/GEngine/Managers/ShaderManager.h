#pragma once
#include <unordered_map>
#include "Assets/Shaders/Shader.h"

//using namespace GEngine::Asset;
//class GEngine::Asset::Shader;

namespace GEngine::Manager
{

	using namespace Asset;

	class ShaderManager
	{

		struct Files
		{
			//std::tuple<types...> keys_filepath;
			std::vector<std::string> keys_filepath;

			Files(const std::initializer_list<std::string>& filePaths)
			{
				keys_filepath.insert(keys_filepath.end(), filePaths);
			}

			operator std::vector<std::string>()const
			{
				return keys_filepath;
			}

			bool operator == (const Files& other) const
			{
				if (keys_filepath.size() != other.keys_filepath.size())return false;
				const size_t size = keys_filepath.size();

				for (size_t i = 0; i < size; i++)
				{
					if (keys_filepath[i] != other.keys_filepath[i])return false;
				}

				return true;
			}

		};

		struct FileHash
		{

		public:
			size_t operator()(const Files& c) const
			{
				size_t seed = 0;
				for (auto& ele : c.keys_filepath)
				{
					//seed ^= std::hash<std::string>{}(ele) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
					seed ^= std::hash<std::string>{}(ele);
				}

				return seed;
			}

		};

		typedef std::unordered_map<Files, Shader*, FileHash> ShaderHashMap;


	public:
		static Shader* GetShaderProgram(const Files& shader_file);
		static void FreeShader();
	
		


	private:
		inline static ShaderHashMap m_ShaderMap;
	};

}