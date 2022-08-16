#pragma once
#include "Actor.h"
#include "Scene.h"

namespace GEngine
{
	class Scene : public Actor
	{
		friend class SceneHiarchyPanel;

	public:
		Scene(): Actor(){}
		Scene(const std::string& name): Actor(name){}

	

	};
}
