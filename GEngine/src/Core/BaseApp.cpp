#include "gepch.h"
#include "Core/BaseApp.h"
#include "Core/RenderTarget.h"
#include <Camera/PerspectiveCamera.h>
#include <Camera/OrthographicCamera.h>
#include "Windows/SDLWindow.h"
#include <imgui/imgui.h>
#include "Managers/ShapeManager.h"
#include "Managers/ShaderManager.h"

//#include "Managers/EventManager.h"

namespace GEngine
{
    BaseApp::BaseApp(): m_LastFrameTime(0.0f)
    {
      
    }

    BaseApp::~BaseApp()
    {

    }

    void BaseApp::Initialize(const WindowProperties& WindowsPropertyList)
    {
        Initialize({ WindowsPropertyList });
    }

    void BaseApp::OnEvent(SDL_Event& e)const
    {
        GetEventManager()->OnEvent(e);
    }

    /*void BaseApp::OnResize(int new_width, int new_height) const
    {

    }

    void BaseApp::OnScroll(float new_zoom) const
    {

    }*/

    void BaseApp::Initialize(const std::initializer_list<WindowProperties>& WindowsPropertyList)
    {

        using namespace Manager;
        using namespace Camera;

        if (!m_Initialize)
        {
            m_GEngine.Initialize(WindowsPropertyList);

            GENGINE_CORE_INFO("Initialize Scene...");
            m_Scene = CreateScopedPtr<Scene>("Scene");
         
            GENGINE_CORE_INFO("Initialize Camera...");
            auto width = WindowsPropertyList.begin()->m_Width;
            auto height = WindowsPropertyList.begin()->m_Height;
            m_EditorCamera = new PerspectiveCamera(
                45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.f);
            m_EditorCamera->SetTag("Editor Camera");
            m_EditorCamera->SetActive(true);

        

            //m_OrthoCamera = new OrthographicCamera();
            //m_OrthoCamera->SetTag("Orthographic Camera");
            //m_OrthoCamera->SetActive(false);

            /*m_Cameras.push_back(m_OrthoCamera);
            m_Cameras.push_back(m_SceneCamera);*/

            m_ProjectionType[0] = false;
            m_ProjectionType[1] = true;


       
            //auto KeyPressEvent = new Events<void()>("KeyPress");
            auto AppCloseEvent = new Events<void()>("AppClose");
            auto AppQuitEvent = new Events<void()>("AppQuit");
            auto WindowResizeEvent = new Events<void(WindowResizeParam)>("WindowResize");
            //auto MouseScrollWheelEvent = new Events<void(MouseScrollWheelParam)>("MouseScrollWheel");

            //MouseScrollWheelEvent->Subscribe([this](const MouseScrollWheelParam& scrollWheelParam)
            //    {
            //        auto& MouseState = GetInputManager()->GetMouseState();
            //        auto& windows = GetWindowManager()->GetWindows();

            //        if (auto p = windows.find(scrollWheelParam.ID); p != windows.end())
            //        {
            //            //GENGINE_CORE_INFO("Mouse scroll wheel at the {}. x: {}   y: {}", p->second->GetTitle(), scrollWheelParam.X, scrollWheelParam.Y);
            //            MouseState.SetScrollWheel(Vector2(
            //                static_cast<float>(scrollWheelParam.X),
            //                static_cast<float>(scrollWheelParam.Y)));

            //            const float clamp_zoom_level = glm::clamp(m_SceneCamera->GetZoomLevel() - 0.03f * scrollWheelParam.Y, 0.4f, 1.3f);
            //            m_SceneCamera->OnScroll(clamp_zoom_level);
            //          
            //        }

            //     

            //       // m_SceneCamera->OnScroll(clamp_zoom_level);

            //    });


            WindowResizeEvent->Subscribe([this](const WindowResizeParam& windowParam)
                {
                   
                    auto& windows = GetWindowManager()->GetWindows();
                    if (auto p = windows.find(windowParam.ID); p != windows.end())
                    {
                        if (windowParam.Width == 0 || windowParam.Height == 0)
                            m_Minimized = true;

                        else 
                            m_Minimized = false;
                        //p->second->OnResize(windowParam.Width, windowParam.Height);
                        //Renderer::SetSurfaceSize(windowParam.Width, windowParam.Height);
                        //m_SceneCamera->OnResize(windowParam.Width, windowParam.Height);
                        //m_SceneCamera->OnResize(winsize.x, winsize.y);
              
                    }
                });

            AppCloseEvent->Subscribe([this]()
                {
                    m_Running = false;

                });

            AppQuitEvent->Subscribe([this]()
                {
                    auto& KeyboardState = GetInputManager()->GetKeyboardState();
                    if (KeyboardState.IsKeyPressed(GENGINE_KEY_ESCAPE))
                    {
                        m_Running = false;
                    }

                });



            //GetEventManager()->GetEventDispatcher().RegisterEvent(MouseScrollWheelEvent);
            //GetEventManager()->GetEventDispatcher().RegisterEvent(WindowResizeEvent);
            GetEventManager()->GetEventDispatcher().RegisterEvent(AppCloseEvent);
            GetEventManager()->GetEventDispatcher().RegisterEvent(AppQuitEvent);

            m_SDLWindow = static_cast<SDLWindow*>(GetWindowManager()->GetInternalWindow(1));
            GetInputManager()->SetSDLWindow(m_SDLWindow);
            
            m_RenderTarget = CreateScopedPtr<RenderTarget>(Vec2f{ m_SDLWindow->GetScreenWidth(), m_SDLWindow->GetScreenHeight() });
            //m_RenderTarget = CreateScopedPtr<RenderTarget>(Vec2f{ 1280, 720 });
            m_Initialize = true;

        }
     
       
    }


    void BaseApp::ProcessInput(Timestep ts)
    {
        SDL_Event event;

        OnEvent(event);


        auto input = GetInputManager();
        input->Update();

        auto& keyboardState = input->GetKeyboardState();
        auto& mouseState = input->GetMouseState();
        if (mouseState.m_XRel != m_LastXRel || mouseState.m_YRel != m_LastYRel)
        {
            m_LastXRel = mouseState.m_XRel;
            m_LastYRel = mouseState.m_YRel;
        }

        else
        {
            mouseState.m_XRel = 0;
            mouseState.m_YRel = 0;
        }

  

       /* if (!mouseState.isButtonPressed(GENGINE_BUTTON_LEFT) && mouseState.isButtonHeld(GENGINE_BUTTON_LEFT))
        {
            GENGINE_CORE_INFO("Mouse button press");
        }*/
  /*      if (mouseState.isButtonPressed(GENGINE_BUTTON_LEFT))
        {
            GENGINE_CORE_INFO("Mouse button pressed");
        }*/

      /*  if (mouseState.isButtonHeld(GENGINE_BUTTON_LEFT))
        {
            GENGINE_CORE_INFO("Mouse button held");
        }

        else if (mouseState.isButtonPressed(GENGINE_BUTTON_LEFT))
        {
            GENGINE_CORE_INFO("Mouse button pressed");
        }

      
  /*      if (m_SDLWindow->GetImGuiWindow()->WantCaptureKeyBoard())
        {
            GENGINE_CORE_INFO("ImGui capture keyboard");
        }

        if (m_SDLWindow->GetImGuiWindow()->WantCaptureMouse())
        {
            GENGINE_CORE_INFO("ImGui capture mouse");
        }*/

        if (keyboardState.IsKeyHeld(GENGINE_KEY_LALT))
        {
            //GENGINE_CORE_INFO("left alt held");
            const Vec2f mouse = { mouseState.GetPosition().x, mouseState.GetPosition().y };
            Vec2f delta = (mouse - m_EditorCamera->GetInitialMousePosition()) * 0.003f;
            m_EditorCamera->GetInitialMousePosition() = mouse;
            if (mouseState.isButtonHeld(GENGINE_BUTTON_LEFT))
                m_EditorCamera->MouseRotate(delta);

            else if (mouseState.isButtonHeld(GENGINE_BUTTON_MIDDLE))
                m_EditorCamera->MousePan(delta);

            //m_EditorCamera->OnUpdateView();
        }

      
       if (mouseState.isButtonPressed(GENGINE_BUTTON_RIGHT) && !m_SDLWindow->GetImGuiWindow()->WantCaptureMouse())  //&& !static_cast<SDLWindow*>(GetWindowManager()->GetInternalWindow(1))->GetImGuiWindow()->WantCaptureMouse())//to do)
        {
            input->SetRelativeMouseMode(true);
            
            //GENGINE_CORE_INFO("relative - PosX: {}, PosY: {}", x, y);

            //if (mouseState.isFirstMouse())
            //{
               // x = 0, y = 0;
                //mouseState.m_LastMouseX = mouseState.m_MousePos.x;
                //mouseState.m_LastMouseY = mouseState.m_MousePos.y;

                //GENGINE_CORE_INFO("relative - LastPosX: {}, LastPosY: {}", mouseState.m_LastMouseX, mouseState.m_LastMouseY);
                //mouseState.SetFirstMouse(false);
        }

        if ((!m_ViewportForcused && m_ViewportHovered) && !mouseState.IsRelative())
        {
            if (keyboardState.IsKeyPressed(GENGINE_KEY_Q))
            {
                m_GizmoType = -1;
            }

            if (keyboardState.IsKeyPressed(GENGINE_KEY_W))
            {
                m_GizmoType = 0;
            }

            if (keyboardState.IsKeyPressed(GENGINE_KEY_E))
            {
                m_GizmoType = 1;
            }

            if (keyboardState.IsKeyPressed(GENGINE_KEY_R))
            {
                m_GizmoType = 2;
            }


            else if (auto& keyboardstate = input->GetKeyboardState(); keyboardstate.IsKeyPressed(GENGINE_KEY_SPACE) && !m_SDLWindow->GetImGuiWindow()->WantCaptureKeyBoard())
            {
                input->SetRelativeMouseMode(false);
                //mouseState.SetFirstMouse(true);
                //GENGINE_CORE_INFO("non relative - xPos: {}, yPos: {}", static_cast<float>(x), static_cast<float>(y));
               /* mouseState.m_CurrentButtons =
                    SDL_GetMouseState(&x, &y);*/
            }
        }

    }

    void BaseApp::Run()
    {
        auto input = GetInputManager();
        auto windows = GetWindowManager();

        //input->SetRelativeMouseMode(true);

        while (m_Running)
        {
            if (!m_Minimized)
            {
                const float time = static_cast<float>(SDL_GetPerformanceCounter());
                const Timestep ts = (time - m_LastFrameTime) / static_cast<float>(SDL_GetPerformanceFrequency());
                m_LastFrameTime = time;


                input->PrepareForUpdate();

                //process input
                ProcessInput(ts);

                //update
                Update(ts);

                //Render scene
                Render();
            }
         
        } 

        
    }

    void BaseApp::Render()
    {
        static int i = 0;
        Renderer::GetRenderStats().m_ArrayDrawCall = 0;
        Renderer::GetRenderStats().m_ElementsDrawCall = 0;
        auto& windows = GetWindowManager()->GetWindows();

        RenderParam param;
        param.ClearColor = { 0.1f, 0.1f, 0.1f, 1.f };
        param.bEnableDepthTest = true;
        param.bClearColorBit = true;
        param.bClearDepthBit = true;
        param.bClearStencilBit = false;

        //Renderer::RenderBegin(m_SceneCamera, true, true, m_RenderTarget.get());
        //Renderer::Clear();
        Renderer::RenderBegin(m_EditorCamera, m_RenderTarget.get());
        Renderer::Set(param);
        Renderer::RenderScene(m_Scene.get(), m_EditorCamera);

        if (m_RenderTarget->IsMultiSampled()) m_RenderTarget->BindAndBlitToScreen();
        //{
        //    m_RenderTarget->BindAndBlitToScreen();
        //    //m_RenderTarget->UnBind();   
        //    param.ClearColor = { 1.f, 1.f, 1.f, 1.f };
        //    param.bClearColorBit = true;
        //    param.bClearDepthBit = false;
        //    param.bClearStencilBit = false;
        //    param.bEnableDepthTest = false;
        //    Renderer::Set(param);
        //    m_AAScreen->Render(m_SceneCamera);*/
        //}
        m_RenderTarget->UnBind();


        for (auto& [windowID, window] : windows)
        {
            auto window_ = static_cast<SDLWindow*>(window.get());
            window_->GetImGuiWindow()->BeginRender(window_);
            ImGuiRender();
            window_->GetImGuiWindow()->EndRender(window_);
            window_->SwapBuffer();
        }

    

        
        //for (auto& [windowID, window] : windows)
        //{
        //    window->BeginRender();
        //
        //    Renderer::RenderBegin(m_SceneCamera, window.get());

        //    //inplemented by derived class inherited from BaseApp
        //   // Update(ts);
        //    Renderer::RenderScene(m_Scene.get(), m_SceneCamera);
        //    window->EndRender(this);
        //
        //}
    }

    void BaseApp::ShutDown()
    {
        m_Running = false; 
    }
}
