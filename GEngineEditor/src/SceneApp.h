#pragma once
#include "Core\BaseApp.h"
#include "Panels/SceneHierarchyPanel.h"





namespace GEngine
{
	class Grid;
	class CameraRig;
	class Entity;


}

namespace GEngine::SceneObjects
{
	class BoxEntity;
}

using namespace GEngine;

class SceneApp: public BaseApp
{
	
public:
	SceneApp(): BaseApp(){}
	~SceneApp() override;

	void Update(Timestep ts) override;
	
	void Initialize(const std::initializer_list<WindowProperties>& WindowsPropertyList)override;
	void Initialize(const WindowProperties& prop = WindowProperties{}) override;

private:
	void ImGuiRender() override;

private:
	ScopedPtr<SceneHierarchyPanel> m_Panel{};
	CameraRig* m_CameraRig{};
	Grid* m_Grid{};

	Entity* m_Sun{};
	Entity* m_Earth{};
	Entity* m_Moon{};
	Entity* m_MilkyWay{};
	SceneObjects::BoxEntity* m_Plane{};

	
	
	//bool m_ViewportForcused = false;
	//bool m_ViewportHovered = false;
	
	//Entity* m_Screen{};
	/*Entity* m_Ico{};
	
	Entity* m_Cylinder{};
	Entity* m_Grass{};
	Entity* m_Torus{};
	Entity* m_Box{};
	Entity* m_EnvironmentSphere{};*/
	
	
};

