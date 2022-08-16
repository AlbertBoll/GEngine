#include "SceneApp.h"
#include "Managers/AssetsManager.h"
#include "Managers/ShapeManager.h"
#include "Managers/ShaderManager.h"
#include "Material/TextureMaterial.h"
#include "Camera/PerspectiveCamera.h"
#include "EntryPoint.h"
#include "Core/Renderer.h"
#include <external/imgui/imgui.h>
#include <GEngine/Core/Log.h>
#include <GEngine/Shapes/SmoothSphere.h>
#include <external/glm/gtc/type_ptr.hpp>
#include <GEngine/Extras/Grid.h>
#include "Core/Entity.h"
#include "Extras/CameraRig.h"
#include "Core/RenderTarget.h"
#include <GEngine/Material/BasicMaterial.h>
#include <SceneObjects/BoxEntity.h>
#include <imguizmo/ImGuizmo.h>
#include <Math/Matrix.h>
#include <Core/SceneGraph.h>

static std::string base_dir = "../GEngine/include/GEngine/Assets/Images/";


SceneApp::~SceneApp()
{
	Manager::AssetsManager::FreeAllResources();
	Manager::ShaderManager::FreeShader();
	Manager::ShapeManager::FreeShape();
}

void SceneApp::Update(Timestep ts)
{
	//Renderer::RenderBegin(m_SceneCamera);
	//m_Sphere->SetPosition(Pos.x, Pos.y, 0.f);
	//m_Sphere_->RotateY(ts, false);
	//m_Plane->GetMaterial()->SetUniforms<bool>({ {"uUseVertexColor", false} });
	

	if (m_ViewportSize.x > 0.f && m_ViewportSize.y > 0.f && (m_RenderTarget->GetWidth() != m_ViewportSize.x || m_RenderTarget->GetHeight() != m_ViewportSize.y))
	{
		m_EditorCamera->OnResize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
		m_RenderTarget->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	m_MilkyWay->RotateY(ts * 0.01f);

	//m_Sun->RotateY(ts);
	
	//m_Earth->RotateY(-ts);
	//m_Earth->RotateY(-ts, false);
	//m_Earth->RotateY(-ts);
	//m_Moon->RotateY(ts);
	//m_Moon->RotateY(-ts);





	//
	
	if (m_ViewportForcused)
	{
		m_CameraRig->Update(ts);
	}

	//Renderer::RenderScene(m_Scene.get(), m_SceneCamera);

}

void SceneApp::Initialize(const std::initializer_list<WindowProperties>& WindowsPropertyList)
{
	using namespace Camera;
	using namespace Manager;
	using namespace Shape;
	using namespace SceneObjects;

	//Initialize BaseApp 
	BaseApp::Initialize(WindowsPropertyList);

	m_Panel = CreateScopedPtr<SceneHierarchyPanel>(this, m_Scene.get());

	//m_Panel->SetContext(m_Scene.get());
	/*m_SkyCamera = CreateScopedPtr<PerspectiveCamera>(45.0f, 1.0f);
	m_SkyCamera->SetTag("SkyCamera");*/

	auto environmentTex = AssetsManager::GetTexture(base_dir + "stars_milky_way.jpg", "uTexture");
	auto environmentTexMaterial = CreateRefPtr<TextureMaterial>(*environmentTex);
	//auto environmentSphere = ShapeManager::_GetShape<SmoothSphere>("EnvironmentSphere", 200.f);
	auto environmentSphere = ShapeManager::GetShape("EnvironmentSphere");
	m_MilkyWay = new Entity(environmentSphere, environmentTexMaterial);
	m_MilkyWay->SetTag("Milky Way");

	auto environmentPlane = ShapeManager::GetShape("Box");
	auto planeMaterial = CreateRefPtr<BasicMaterial>();
	m_Plane = new BoxEntity(environmentPlane, planeMaterial);
	m_Plane->SetTag("Plane");
	m_Plane->SetPosition({ -8, 0, 0 });
	m_Plane->Scale(2);
	

	auto SunTex = AssetsManager::GetTexture(base_dir + "sun.jpg", "uTexture");
	auto EarthTex = AssetsManager::GetTexture(base_dir + "earth_day.jpg", "uTexture");
	auto MoonTex = AssetsManager::GetTexture(base_dir + "moon.jpg", "uTexture");
	auto SunMaterial = CreateRefPtr<TextureMaterial>(*SunTex);
	auto EarthMaterial = CreateRefPtr<TextureMaterial>(*EarthTex);
	auto MoonMaterial = CreateRefPtr<TextureMaterial>(*MoonTex);
	auto sphereGeo = ShapeManager::GetShape("SmoothSphere");
	m_Grid = new Grid(60, 20);
	m_Grid->RotateX(Math::PiOver2);
	m_Grid->SetTag("World Grid");

	m_Sun = new Entity(sphereGeo, SunMaterial);
	m_Sun->SetTag("Sun");

	m_Earth = new Entity(sphereGeo, EarthMaterial);
	m_Earth->SetTag("Earth");

	m_Moon = new Entity(sphereGeo, MoonMaterial);
	m_Moon->SetTag("Moon");

	m_Sun->Scale(3.f, false);
	m_Earth->Scale(1/3.f);
	m_Moon->Scale(1 / 2.f, true);

	m_MilkyWay->GetRenderSetting().m_RenderMode = RenderMode::Elements;
	m_MilkyWay->GetRenderSetting().m_Mode = DrawMode::TRIANGLE_STRIP;

	m_Sun->GetRenderSetting().m_RenderMode = RenderMode::Elements;
	m_Sun->GetRenderSetting().m_Mode = DrawMode::TRIANGLE_STRIP;

	m_Earth->GetRenderSetting().m_RenderMode = RenderMode::Elements;
	m_Earth->GetRenderSetting().m_Mode = DrawMode::TRIANGLE_STRIP;

	m_Moon->GetRenderSetting().m_RenderMode = RenderMode::Elements;
	m_Moon->GetRenderSetting().m_Mode = DrawMode::TRIANGLE_STRIP;
	

	m_Sun->SetPosition({ 0.0, 0.f, 0.f });
	
	m_Scene->Add(m_MilkyWay);
	m_Scene->Add(m_Sun);
	m_Sun->Add(m_Earth);
	m_Earth->Add(m_Moon);
	

	m_Earth->SetPosition({ 3.5f, 0.f, 0.f });
	m_Moon->SetPosition({ 6.5f, 0.0f, 0.0f });
	//m_CameraRig = CreateScopedPtr<CameraRig>(true);
	m_CameraRig =new CameraRig(true);
	m_CameraRig->SetTag("Camera Rig");

	m_CameraRig->SetPosition({ 0.f, 8.f, 20.f });

	m_CameraRig->Attach(m_EditorCamera);

	m_Scene->Add(m_CameraRig);
	m_Scene->Add(m_Grid);
	
	m_Scene->Add(m_Plane);

	SceneGraph::GenerateSceneGraph(m_Scene.get());
	//m_SceneCamera->SetTag("Scene Camera");

	auto MouseScrollWheelEvent = new Events<void(MouseScrollWheelParam)>("MouseScrollWheel");

	MouseScrollWheelEvent->Subscribe([this](const MouseScrollWheelParam& scrollWheelParam)
		{
			if (m_ViewportForcused && m_ViewportHovered)
			{
				auto& MouseState = GetInputManager()->GetMouseState();
				auto& windows = GetWindowManager()->GetWindows();

				if (auto p = windows.find(scrollWheelParam.ID); p != windows.end())
				{
					//GENGINE_CORE_INFO("Mouse scroll wheel at the {}. x: {}   y: {}", p->second->GetTitle(), scrollWheelParam.X, scrollWheelParam.Y);
					MouseState.SetScrollWheel(Vector2(
						static_cast<float>(scrollWheelParam.X),
						static_cast<float>(scrollWheelParam.Y)));
					//const float clamp_zoom_level = glm::clamp(m_CameraSetting.m_PerspectiveSetting.m_FieldOfView * new_zoom_level, 15.f, 90.f);
					//const float clamp_zoom_level = glm::clamp(m_SceneCamera->GetZoomLevel() - 0.03f * scrollWheelParam.Y, 0.2f, 1.5f);
					//m_SceneCamera->OnScroll(clamp_zoom_level);
				
					m_EditorCamera->OnScroll(scrollWheelParam.Y);

				}

			}

		});

	GetEventManager()->GetEventDispatcher().RegisterEvent(MouseScrollWheelEvent);

	

}

void SceneApp::Initialize(const WindowProperties& prop)
{
	using namespace Camera;
	using namespace Manager;

	//Initialize BaseApp 
	BaseApp::Initialize(prop);

	Initialize({ prop });
	
	
}

void SceneApp::ImGuiRender()
{
	using namespace Manager;

	/*ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	if (ImGui::Begin("Earth Pos X"))
	{
		ImGui::DragFloat("Eath Pos X", &Pos.x, 0.1f);

	}
	ImGui::End();

	if (ImGui::Begin("Earth Pos Y"))
		ImGui::DragFloat("Eath Pos Y", &Pos.y, 0.1f);
	


	ImGui::End();

	if (ImGui::Begin("Textures"))
	{
		if (ImGui::Button("Default"))
		{
			auto DefaultTex = AssetsManager::GetTexture();
			auto DefaultTexMaterial = CreateRefPtr<TextureMaterial>(*DefaultTex);
			m_Sphere->SetMaterial(DefaultTexMaterial);
		}

		if (ImGui::Button("Water"))
		{
			auto waterTex = AssetsManager::GetTexture(base_dir + "water.jpg");
			auto waterTexMaterial = CreateRefPtr<TextureMaterial>(*waterTex);
			m_Sphere->SetMaterial(waterTexMaterial);
		}

		if (ImGui::Button("Earth"))
		{
			auto earthTex = AssetsManager::GetTexture(base_dir + "earth.jpg");
			auto earthTexMaterial = CreateRefPtr<TextureMaterial>(*earthTex);
			m_Sphere->SetMaterial(earthTexMaterial);
		}
	}
	ImGui::End();
	
	ImGui::Begin("GameView1");


	auto winsize = ImGui::GetWindowSize();
	if (ImGui::IsWindowHovered())
	{
		ImGui::CaptureMouseFromApp(false);
	}
	ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), winsize, { 0,1 }, { 1, 0 });
	ImGui::End();*/

	/*ImGui::Begin("GameView2");
	if (ImGui::IsWindowHovered())
	{
		ImGui::CaptureMouseFromApp(false);
	}
	ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), { 480, 320 }, { 0,1 }, { 1, 0 });
	ImGui::End();

	ImGui::Begin("GameView3");
	if (ImGui::IsWindowHovered())
	{
		ImGui::CaptureMouseFromApp(false);
	}
	ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), { 480, 320 }, { 0,1 }, { 1, 0 });
	ImGui::End();

	ImGui::Begin("GameView4");
	if (ImGui::IsWindowHovered())
	{
		ImGui::CaptureMouseFromApp(false);
	}
	ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), { 480, 320 }, { 0,1 }, { 1, 0 });
	ImGui::End();*/



	//ImGui::End();

	//ImGui::Begin("View2");
	/*if (ImGui::IsWindowHovered())
	{
		ImGui::CaptureMouseFromApp(false);
	}*/
	//ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), { 100, 100 }, { 0,1 }, { 1, 0 });
	//ImGui::End();

	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	static bool show = true;
	//ImGui::ShowDemoWindow(&show);

	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	//// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	//// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	//// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	//// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	//// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	//// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	//// all active windows docked into it will lose their parent and become undocked.
	//// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	//// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &show, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	//// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();

	auto& style = ImGui::GetStyle();
	float winMinSize = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = winMinSize;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", nullptr, &opt_fullscreen);
			//ImGui::MenuItem("Padding", nullptr, &opt_padding);
			//ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
			{
				ShutDown();
			}

			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}

	m_Panel->OnImGuiRender();

	ImGui::Begin("Stats");

	auto stats = Renderer::GetRenderStats();
	ImGui::Text("Renderer Stats:");

	ImGui::Text("ArrayDraw Calls: %d", stats.m_ArrayDrawCall);
	ImGui::Text("ElementsDraw Calls: %d", stats.m_ElementsDrawCall);

	ImGui::Text("Vertices: %d", stats.m_VerticeCount);

	ImGui::Text("Indices: %d", stats.m_IndicesCount);

	if (m_Sun)
	{
		ImGui::Separator();
		ImGui::Text("%s", m_Sun->GetTag().c_str());
		Vec3f pos = m_Sun->GetWorldPosition();
		ImGui::DragFloat3("Sun Pos", glm::value_ptr(pos), 0.1f);
		ImGui::Separator();

		if (m_Earth)
		{

			ImGui::Separator();
			ImGui::Text("%s", m_Earth->GetTag().c_str());
			pos = m_Earth->GetWorldPosition();
			ImGui::DragFloat3("Earth Pos", glm::value_ptr(pos), 0.1f);
			ImGui::Separator();

			if (m_Moon)
			{
				ImGui::Separator();
				ImGui::Text("%s", m_Moon->GetTag().c_str());
				pos = m_Moon->GetWorldPosition();
				ImGui::DragFloat3("Moon Pos", glm::value_ptr(pos), 0.1f);
				ImGui::Separator();
			}
		}
		
	}


	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

	//ImGui::Begin("Settings");
	////const auto IronAlbedoTex = GraphicEngine::ResourceManager::GetTexture(BaseImageFilePath + "RustedIron/albedo.png", "albedoMap");
	//ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetTargetTextureID()), { 800,600 }, { 0,1 }, { 1, 0 });
	//ImGui::End();

	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//if (ImGui::Begin("Earth Pos X"))
	//{
	//	ImGui::DragFloat("Eath Pos X", &Pos.x, 0.1f);

	//}
	//ImGui::End();

	//if (ImGui::Begin("Earth Pos Y"))
	//	ImGui::DragFloat("Eath Pos Y", &Pos.y, 0.1f);



	//ImGui::End();

	//if (ImGui::Begin("Textures"))
	//{
	//	if (ImGui::Button("Default"))
	//	{
	//		auto DefaultTex = AssetsManager::GetTexture();
	//		auto DefaultTexMaterial = CreateRefPtr<TextureMaterial>(*DefaultTex);
	//		m_Sphere->SetMaterial(DefaultTexMaterial);
	//	}

	//	if (ImGui::Button("Water"))
	//	{
	//		auto waterTex = AssetsManager::GetTexture(base_dir + "water.jpg");
	//		auto waterTexMaterial = CreateRefPtr<TextureMaterial>(*waterTex);
	//		m_Sphere->SetMaterial(waterTexMaterial);
	//	}

	//	if (ImGui::Button("Earth"))
	//	{
	//		auto earthTex = AssetsManager::GetTexture(base_dir + "earth.jpg");
	//		auto earthTexMaterial = CreateRefPtr<TextureMaterial>(*earthTex);
	//		m_Sphere->SetMaterial(earthTexMaterial);
	//	}
	//}
	//ImGui::End();
	ImGui::Begin("Viewport");

	m_ViewportForcused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	//GENGINE_INFO("Focused: {}", ImGui::IsWindowFocused());
	//GENGINE_INFO("Hovered: {}", ImGui::IsWindowHovered());

	auto viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
	
	/*if (m_ViewportSize != *((Vec2f*)(&viewportPanelSize)) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
	{
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		m_SceneCamera->OnResize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
		m_RenderTarget->OnResize( (uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y );
	}*/

	//GENGINE_WARN()
	//auto winsize = ImGui::GetWindowSize();
	if (m_ViewportHovered)
	{
		ImGui::CaptureMouseFromApp(false);
		
		//GENGINE_CORE_INFO("Hoverd");
	}

	if (m_ViewportForcused)
	{
		ImGui::CaptureKeyboardFromApp(true);
	}



	if(!m_RenderTarget->IsMultiSampled())
		ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetColorAttachmentID()), { m_ViewportSize.x, m_ViewportSize.y }, { 0,1 }, { 1, 0 });
	else
		ImGui::Image(reinterpret_cast<void*>(m_RenderTarget->GetScreenAttachmentID()), { m_ViewportSize.x, m_ViewportSize.y }, { 0,1 }, { 1, 0 });
	
	//Gizmos

	float winWidth{};
	float winHeight{};



	Actor* selectActor = m_Panel->GetSelectedEntity();


	if(m_ViewportForcused||m_ViewportHovered)
	{ 
		if (selectActor && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			winWidth = ImGui::GetWindowWidth();
			winHeight = ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, winWidth, winHeight);
			auto view = m_EditorCamera->GetView();
			auto projection = m_EditorCamera->GetProjection();

			auto& tc = selectActor->GetLocalTransformation();
			auto& transform = tc.Transform;
			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));
			if (ImGuizmo::IsUsing())
			{
				Vec3f translation, rotation, scale;
				if (Matrix::DecomposeTransform(transform, translation, rotation, scale))
				{
					tc.Translation = translation;
					Vec3f deltaRotation = Math::ToDegrees(rotation) - tc.Rotation;
					tc.Rotation += deltaRotation;

					tc.Scale = scale;
				}


			}

		}
	}
	
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}


BaseApp* CreateApp()
{
	return new SceneApp();
}