#include "gepch.h"
#include "SceneObjects/_Scene.h"
#include <Component/Component.h>
#include <SceneObjects/_Entity.h>

namespace GEngine
{
	using namespace Component;
	_Scene::_Scene()
	{
		auto entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity);

	

		if (m_Registry.any_of<TransformComponent>(entity))
		{
			auto& transform = m_Registry.get<TransformComponent>(entity);
		}
	}

	_Scene::~_Scene()
	{

	}

	void _Scene::Update(Timestep ts)
	{

	}
	_Entity _Scene::CreateEntity(const std::string& tag)
	{
		_Entity entity = {m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(tag);
		return entity;
	}
}