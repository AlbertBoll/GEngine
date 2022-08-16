#include"gepch.h"
#include"Core/SceneGraph.h"
#include"Core/Actor.h"

namespace GEngine
{
	void SceneGraph::GenerateSceneGraph(Actor* scene)
	{
		for (auto child : scene->GetChildrenRef())
		{
			m_Scene[child->GetID()] = child;
			GenerateSceneGraph(child);
		}
	}

	Actor* SceneGraph::GetActorFromUUID(UUID uuid)
	{
		if (auto it = m_Scene.find(uuid); it != m_Scene.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void SceneGraph::RemoveActorFromUUID(UUID uuid)
	{
		if (auto it = m_Scene.find(uuid); it != m_Scene.end())
		{

			m_Scene.erase(uuid);
		}
	}
	void SceneGraph::AddToScene(Actor* actor)
	{
		if (auto it = m_Scene.find(actor->GetID()); it == m_Scene.end())
		{

			m_Scene[actor->GetID()] = actor;
		}
	}

}
