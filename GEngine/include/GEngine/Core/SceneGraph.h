#pragma once
#include <unordered_map>
#include <Core/UUID.h>

namespace GEngine
{
	class Actor;

	class SceneGraph
	{

	public:
		static void GenerateSceneGraph(Actor* scene);
		static Actor* GetActorFromUUID(UUID uuid);
		static void RemoveActorFromUUID(UUID uuid);
		static void AddToScene(Actor* actor);


	private:
		inline static std::unordered_map<UUID, Actor*> m_Scene;
	};
}
