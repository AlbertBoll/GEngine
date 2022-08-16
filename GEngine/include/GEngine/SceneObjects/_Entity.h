#pragma once
#include <entt/entt.hpp>
#include <SceneObjects/_Scene.h>

namespace GEngine
{
	class _Entity
	{
	public:
		_Entity() = default;
		_Entity(entt::entity handle, _Scene* scene);
		~_Entity();

		template<typename... Args>
		bool HasComponents() const
		{
			m_Scene->Reg().all_of<Args...>(m_EntityHandle);
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&&...args)
		{
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		void RemoveComponents()
		{
			return m_Scene->m_Registry.remove<T, Args...>(m_EntityHandle);
		}

		operator entt::entity() { return m_EntityHandle; }

		operator entt::entity() const { return m_EntityHandle; }

		operator bool() const { return  m_EntityHandle != entt::null; }

	private:
		entt::entity m_EntityHandle{entt::null};
		_Scene* m_Scene{};
	};

}
