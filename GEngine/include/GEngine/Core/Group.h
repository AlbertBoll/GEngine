#pragma once

#include"Actor.h"
#include <vector>
#include <string>
#include "Assets/Shaders/Shader.h"
#include "Managers/ShaderManager.h"

namespace GEngine
{

	template<typename T, typename = std::enable_if_t<std::is_base_of_v<Actor, T>>>
	class Group : public Actor
	{
		
		typedef typename std::vector<T> Collections;
		typedef typename Collections::iterator iterator;
		typedef typename Collections::const_iterator const_iterator;

	public:
		Group() = default;

		Group(std::vector<T> objects) : Object3D(), m_Group(std::move(objects))
		{

		}

		void Push(const T& object) { m_Group.emplace_back(object); }
		void Push(T&& object) { m_Group.push_back(std::move(object)); }
		//void Push(T&& object) { m_Group.emplace_back(std::move(object)); }

		void Push(const std::vector<T>& objects) { m_Group.insert(m_Group.end(), objects.begin(), objects.end()); }

		void Remove(const T& object)
		{
			m_Group.erase(std::remove(m_Group.begin(), m_Group.end(), object), m_Group.end());
		}

		void Render(const Camera& camera) override
		{
			//m_Shader->Use();

			for (auto& obj : m_Group)
			{
				obj.Render(camera);
			}
		}

		T& operator[](int i) { return m_Group[i]; }
		inline iterator begin() noexcept { return  m_Group.begin(); }
		inline const_iterator cbegin() const noexcept { return  m_Group.cbegin(); }
		inline iterator end() noexcept { return  m_Group.end(); }
		inline const_iterator cend() const noexcept { return  m_Group.cend(); }

		void SetShader(Asset::Shader* shader) { m_Shader = shader; }
		void SetShader(const std::initializer_list<std::string>& files)
		{
			using namespace GEngine::Manager;
			const ShaderManager::Files _files{ files };
			m_Shader = ShaderManager::GetShaderProgram(_files);
		}

	private:
		Collections m_Group;
		Asset::Shader* m_Shader{};
	};
}
