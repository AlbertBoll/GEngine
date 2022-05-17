#include "gepch.h"

#include "Managers/EventManager.h"
#include "Managers/WindowManager.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/ApplicationEvent.h"
#include "Core/BaseApp.h"


using namespace GEngine::Event;


namespace GEngine::Manager
{

	struct MouseScrollWheelParam
	{
		unsigned int ID;
		float X;
		float Y;
	};
	

	struct MouseMoveParam
	{
		unsigned int ID;
		int32_t XPos;
		int32_t YPos;
	};

	struct MouseButtonParam
	{
		
		unsigned int ID;
		int32_t X;
		int32_t Y;
		uint8_t Button;
		uint8_t Clicks;
	};

	struct WindowCloseParam
	{

		unsigned int ID;
	};


	struct WindowResizeParam
	{
		unsigned int ID;
		int Width;
		int Height;
	};


	ScopedPtr<EventManager> EventManager::GetScopedInstance()
	{
		struct MkUniEnablr : public EventManager {};
		auto instance = CreateScopedPtr<MkUniEnablr>();

		return instance;
	}


	void EventManager::Initialize()
	{	
		using namespace GEngine;

		auto AppQuitEvent = new Events<void()>("AppQuit");
		auto WindowCloseEvent = new Events<void(WindowCloseParam)>("WindowClose");
		auto WindowResizeEvent = new Events<void(WindowResizeParam)>("WindowResize");
		auto KeyPressEvent = new Events<void(const char*)>("KeyPress");
		auto KeyRepeatEvent = new Events<void(const char*)>("KeyRepeat");
		auto KeyReleaseEvent = new Events<void(const char*)>("KeyRelease");
		auto MouseButtonPressEvent = new Events<void(MouseButtonParam)>("MouseButtonPress");
		auto MouseButtonReleaseEvent = new Events<void(MouseButtonParam)>("MouseButtonRelease");
		auto MouseMoveEvent = new Events<void(MouseMoveParam)>("MouseMove");
		auto MouseScrollWheelEvent = new Events<void(MouseScrollWheelParam)>("MouseScrollWheel");


		MouseScrollWheelEvent->Subscribe([](const MouseScrollWheelParam& scrollWheelParam)
			{
				auto& engine = BaseApp::GetEngine();
				auto* inputManager = engine.GetInputManager();
				auto& MouseState = inputManager->GetMouseState();

				if (auto p = engine.GetWindowManager()->GetWindows().find(scrollWheelParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					GENGINE_CORE_INFO("Mouse scroll wheel at the {}. x: {}   y: {}", p->second->GetTitle(), scrollWheelParam.X, scrollWheelParam.Y);
				}

				MouseState.SetScrollWheel(Vector2(
					static_cast<float>(scrollWheelParam.X),
					static_cast<float>(scrollWheelParam.Y)));
			});


		MouseMoveEvent->Subscribe([](const MouseMoveParam& moveParam)
			{
				auto& engine = BaseApp::GetEngine();
				if (auto p = engine.GetWindowManager()->GetWindows().find(moveParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					GENGINE_CORE_INFO("Mouse moves to the {}. xPos: {}   yPos: {}", p->second->GetTitle(), moveParam.XPos, moveParam.YPos);
				}

			});


		MouseButtonReleaseEvent->Subscribe([](const MouseButtonParam& buttonParam)
			{
				auto& engine = BaseApp::GetEngine();
				if (auto p = engine.GetWindowManager()->GetWindows().find(buttonParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					if (buttonParam.Button == SDL_BUTTON_LEFT)
						GENGINE_CORE_INFO("Left Mouse button was release at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
					else if (buttonParam.Button == SDL_BUTTON_MIDDLE)
						GENGINE_CORE_INFO("Middle Mouse button was release at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
					else
						GENGINE_CORE_INFO("Right Mouse button was release at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
				}
			});



		MouseButtonPressEvent->Subscribe([](const MouseButtonParam& buttonParam)
			{
				auto& engine = BaseApp::GetEngine();
				if (auto p = engine.GetWindowManager()->GetWindows().find(buttonParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					if (buttonParam.Button == SDL_BUTTON_LEFT)
					{
						if (buttonParam.Clicks == 1)
							GENGINE_CORE_INFO("Left mouse button was clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
						else
							GENGINE_CORE_INFO("Left mouse button was double clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
					}

					else if (buttonParam.Button == SDL_BUTTON_MIDDLE)
					{
						if (buttonParam.Clicks == 1)
							GENGINE_CORE_INFO("Middle mouse button was clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
						else
							GENGINE_CORE_INFO("Middle mouse button was double clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
					}

					else
					{
						if (buttonParam.Clicks == 1)
							GENGINE_CORE_INFO("Right mouse button was clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
						else
							GENGINE_CORE_INFO("Right mouse button was double clicked at {}. Window coords ({}, {})", p->second->GetTitle(), buttonParam.X, buttonParam.Y);
					}
				}
			});


		KeyPressEvent->Subscribe([](const char* keyName)
			{
				GENGINE_CORE_INFO("Key {} was pressed", keyName);
			});

		KeyRepeatEvent->Subscribe([](const char* keyName)
			{
				GENGINE_CORE_INFO("Key {} was repeated", keyName);
			});

		KeyReleaseEvent->Subscribe([](const char* keyName)
			{
				GENGINE_CORE_INFO("Key {} was released", keyName);
			});


		AppQuitEvent->Subscribe([]()
			{

				auto& engine = BaseApp::GetEngine();
				
				engine.ShutDown();
			});

		WindowCloseEvent->Subscribe(([](WindowCloseParam windowParam)
			{
				auto& engine = BaseApp::GetEngine();
				if (auto p = engine.GetWindowManager()->GetWindows().find(windowParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					GENGINE_CORE_INFO("Window with ID {} was closed", windowParam.ID);
					engine.GetWindowManager()->RemoveWindow(windowParam.ID);
					GENGINE_CORE_INFO("Window Manager Size {}", engine.GetWindowManager()->GetWindows().size());

					auto& numWindows = engine.GetWindowManager()->GetNumOfWindows();
					if (--numWindows == 0) {
						engine.ShutDown();
						GENGINE_CORE_INFO("ShutDown!");

					}
				}
			}));

		WindowResizeEvent->Subscribe([](const WindowResizeParam& windowParam)
			{
				
				auto& engine = BaseApp::GetEngine();
				if (auto p = engine.GetWindowManager()->GetWindows().find(windowParam.ID); p != engine.GetWindowManager()->GetWindows().end())
				{
					p->second->OnResize(windowParam.Width, windowParam.Height);
				}
			});


		m_EventDispatcher.RegisterEvent(AppQuitEvent);
		m_EventDispatcher.RegisterEvent(WindowCloseEvent);
		m_EventDispatcher.RegisterEvent(WindowResizeEvent);
		m_EventDispatcher.RegisterEvent(KeyPressEvent);
		m_EventDispatcher.RegisterEvent(KeyRepeatEvent);
		m_EventDispatcher.RegisterEvent(KeyReleaseEvent);
		m_EventDispatcher.RegisterEvent(MouseButtonPressEvent);
		m_EventDispatcher.RegisterEvent(MouseButtonReleaseEvent);
		m_EventDispatcher.RegisterEvent(MouseMoveEvent);
		m_EventDispatcher.RegisterEvent(MouseScrollWheelEvent);


	}



	void EventManager::OnEvent(SDL_Event& e)
	{

		while(SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				m_EventDispatcher.DispatchEvent("AppQuit");
				break;

			case SDL_KEYDOWN:
				if (!e.key.repeat) 
					m_EventDispatcher.DispatchEvent("KeyPress", SDL_GetKeyName(e.key.keysym.sym));  

				else 
					m_EventDispatcher.DispatchEvent("KeyRepeat", SDL_GetKeyName(e.key.keysym.sym));
				break;

			case SDL_KEYUP:
				m_EventDispatcher.DispatchEvent("KeyRelease", SDL_GetKeyName(e.key.keysym.sym));
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_EventDispatcher.DispatchEvent("MouseButtonPress", MouseButtonParam{ .ID = e.button.windowID, 
																					   .X = e.button.x, 
					                                                                   .Y = e.button.y ,
					                                                                   .Button = e.button.button, 
					                                                                   .Clicks = e.button.clicks });
			
				break;

			case SDL_MOUSEBUTTONUP:
				m_EventDispatcher.DispatchEvent("MouseButtonRelease", MouseButtonParam{ .ID = e.button.windowID,
																					    .X = e.button.x,
																					    .Y = e.button.y ,
																					    .Button = e.button.button,
																					    .Clicks = e.button.clicks });

				break;


			case SDL_MOUSEWHEEL:
				
				m_EventDispatcher.DispatchEvent("MouseScrollWheel", MouseScrollWheelParam{ .ID = e.wheel.windowID,
																						   .X = e.wheel.preciseX,
																						   .Y = e.wheel.preciseY});
				break;

			case SDL_MOUSEMOTION:
				m_EventDispatcher.DispatchEvent("MouseMove", MouseMoveParam{ .ID = e.button.windowID,
																			 .XPos = e.button.x,
																			 .YPos = e.button.y });
				break;

			case SDL_WINDOWEVENT:
			{

				if (e.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					m_EventDispatcher.DispatchEvent("WindowClose", WindowCloseParam{ .ID = e.window.windowID });
				}

				else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					m_EventDispatcher.DispatchEvent("WindowResize", WindowResizeParam{ .ID = e.window.windowID, 
						                                                               .Width =  e.window.data1, 
						                                                               .Height = e.window.data2 });
				}

				break;


			}
			
			}
		}
	}


}