#pragma once

//#include <GEngine/Core/Scene.h>
namespace GEngine
{
	class BaseApp;
	class Scene;
	class SceneHierarchyPanel
	{

		friend class Actor;
	public:

		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(BaseApp* app, Scene* context);

		void SetContext(Scene* context);

		void OnImGuiRender();

		void DrawComponents(Actor* actor);

		Actor* GetSelectedEntity() const { return m_SelectedContext; }

	private:
		void DrawEntityNode(Actor* actor);

	private:
		BaseApp* m_App{};

		Scene* m_Context{};

		Actor* m_SelectedContext{};

		

	};

}