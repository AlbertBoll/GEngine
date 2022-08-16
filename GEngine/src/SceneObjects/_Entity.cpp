#include "gepch.h"
#include "SceneObjects/_Entity.h"
#include <SceneObjects/_Scene.h>

namespace GEngine
{
	_Entity::~_Entity()
	{

	}
	_Entity::_Entity(entt::entity handle, _Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
	{

	}

}