#pragma once
#include"entt/entt.hpp"
#include <Core/Timestep.h>

namespace GEngine
{
	class _Entity;
	class _Scene
	{
		
		friend class _Entity;

	public:

		_Scene();
		~_Scene();
		
		void Update(Timestep ts);

		entt::registry& Reg() { return m_Registry; }

		_Entity CreateEntity(const std::string& tag = " ");

	private:
		entt::registry m_Registry;
	};


}