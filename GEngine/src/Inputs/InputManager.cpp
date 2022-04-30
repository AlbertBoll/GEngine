#include "gepch.h"
//#include "sdl2/SDL.h"
#include "Inputs/InputManager.h"
#include "Core/BaseApp.h"
#include "Core/WindowManager.h"

namespace GEngine
{



    ButtonState KeyboardState::GetKeyState(GEngineKeyCode keyCode) const
    {
        if (m_PreviousState[keyCode] == 0)
        {
            if (m_CurrentState[keyCode] == 0)
            {
                return ButtonState::None;
            }

            else
                return ButtonState::Pressed;
        }

        else
        {
            if (m_CurrentState[keyCode] == 0)
            {
                return ButtonState::Released;
            }

            else
                return ButtonState::Held;
        }
    }

    bool MouseState::GetButtonValue(int button) const
    {
        return (GENGINE_BUTTON(button) & m_CurrentButtons) == 1;
    }

    ButtonState MouseState::GetButtonState(int button) const
    {
        const int mask = GENGINE_BUTTON(button);

        if ((mask & m_PreviousButtons) == 0)
            if ((mask & m_CurrentButtons) == 0)
            {
                return ButtonState::None;
            }

            else
                return ButtonState::Pressed;

        else
            if ((mask & m_CurrentButtons) == 0)
            {
                return ButtonState::Released;
            }

            else
                return ButtonState::Held;
    }




    bool ControllerState::GetButtonValue(GEngineControllerCode button) const
    {
        return m_CurrentButtons[button] == 1;
    }


    ButtonState ControllerState::GetButtonState(GEngineControllerCode button) const
    {
        if (m_PreviousButtons[button] == 0)
        {
            if (m_CurrentButtons[button] == 0)
            {
                return ButtonState::None;
            }

            else
                return ButtonState::Pressed;
        }

        else
            if (m_CurrentButtons[button] == 0)
            {
                return ButtonState::Released;
            }

            else
                return ButtonState::Held;

    }


  /*  InputManager& InputManager::Get()
    {
        static InputManager inputManager;
        return inputManager;
    }*/

    ScopedPtr<InputManager> InputManager::GetScopedInstance()
    {
        struct MkUniEnablr : public InputManager {};
        auto instance = CreateScopedPtr<MkUniEnablr>();
        // do something with instance

        return instance;
    }

    void InputManager::Initialize()
    {
        // Keyboard
        // Assign current state pointer
        m_InputState.m_Keyboard.m_CurrentState = SDL_GetKeyboardState(nullptr);

        // Clear previous Keyboard state memory
        memset(m_InputState.m_Keyboard.m_PreviousState, 0,
            GENGINE_MAX_KEYCODES);

        // Mouse (just set everything to 0)
        m_InputState.m_Mouse.m_CurrentButtons = 0;
        m_InputState.m_Mouse.m_PreviousButtons = 0;

        // Get the connected controller, if it exists
        m_GameController = SDL_GameControllerOpen(0);

        // Initialize controller state
        m_InputState.m_Controller.m_IsConnected = (m_GameController != nullptr);

        memset(m_InputState.m_Controller.m_CurrentButtons, 0,
            GENGINE_CONTROLLER_BUTTON_MAX);
        memset(m_InputState.m_Controller.m_PreviousButtons, 0,
            GENGINE_CONTROLLER_BUTTON_MAX);
    }


    void InputManager::ShutDown()
    {

    }


    void InputManager::PrepareForUpdate()
    {
        // Copy current state to previous
        // Keyboard
        memcpy(m_InputState.m_Keyboard.m_PreviousState,
            m_InputState.m_Keyboard.m_CurrentState,
            GENGINE_MAX_KEYCODES);

        // Mouse
        m_InputState.m_Mouse.m_PreviousButtons = m_InputState.m_Mouse.m_CurrentButtons;


        if (m_InputState.m_Controller.m_IsConnected)
        {
            // Controller
            memcpy(m_InputState.m_Controller.m_PreviousButtons,
                m_InputState.m_Controller.m_CurrentButtons,
                GENGINE_CONTROLLER_BUTTON_MAX);

        }
    }

    void InputManager::Update()
    {
        int x = 0, y = 0;
        if (m_InputState.m_Mouse.m_IsRelative)
        {
            m_InputState.m_Mouse.m_CurrentButtons =
                SDL_GetRelativeMouseState(&x, &y);
        }
        else
        {
            m_InputState.m_Mouse.m_CurrentButtons =
                SDL_GetMouseState(&x, &y);
        }


        m_InputState.m_Mouse.m_MousePos.x = static_cast<float>(x);
        m_InputState.m_Mouse.m_MousePos.y = static_cast<float>(y);

        // Controller
        // Buttons
        if (m_InputState.m_Controller.m_IsConnected)
        {
            for (int i = 0; i < GENGINE_CONTROLLER_BUTTON_MAX; i++)
            {
                m_InputState.m_Controller.m_CurrentButtons[i] =
                    SDL_GameControllerGetButton(m_GameController,
                        static_cast<SDL_GameControllerButton>(i));
            }

            // Triggers
            m_InputState.m_Controller.m_LeftTrigger =
                Filter1D(SDL_GameControllerGetAxis(m_GameController,
                    SDL_CONTROLLER_AXIS_TRIGGERLEFT));
            m_InputState.m_Controller.m_RightTrigger =
                Filter1D(SDL_GameControllerGetAxis(m_GameController,
                    SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

            // Sticks
            x = SDL_GameControllerGetAxis(m_GameController,
                SDL_CONTROLLER_AXIS_LEFTX);
            y = -SDL_GameControllerGetAxis(m_GameController,
                SDL_CONTROLLER_AXIS_LEFTY);
            m_InputState.m_Controller.m_LeftStick = Filter2D(x, y);

            x = SDL_GameControllerGetAxis(m_GameController,
                SDL_CONTROLLER_AXIS_RIGHTX);
            y = -SDL_GameControllerGetAxis(m_GameController,
                SDL_CONTROLLER_AXIS_RIGHTY);
            m_InputState.m_Controller.m_RightStick = Filter2D(x, y);

        }
    }


    void InputManager::ProcessEvent(SDL_Event& event)
    {
        auto& engine = BaseApp::GetEngine();
        auto* windowsManager = engine.GetWindowManager();
        switch (event.type)
        {

        case SDL_MOUSEMOTION:
            if (auto p = windowsManager->GetWindows().find(event.motion.windowID); p != windowsManager->GetWindows().end())
            {
                GENGINE_CORE_INFO("Mouse moves to the {}. xPos: {}   yPos: {}", p->second->GetTitle(), event.motion.x, event.motion.y);
            }
            break;
        
        case SDL_KEYDOWN:
            
            //auto character = event.key.keysym.sym;
            GENGINE_CORE_INFO("Key {} was pressed", SDL_GetKeyName(event.key.keysym.sym));
            break;

        case SDL_KEYUP:

            //auto character = event.key.keysym.sym;
            GENGINE_CORE_INFO("Key {} was Release", SDL_GetKeyName(event.key.keysym.sym));
            break;
        

        case SDL_MOUSEWHEEL:
            m_InputState.m_Mouse.m_ScrollWheel = Vector2(
                static_cast<float>(event.wheel.x),
                static_cast<float>(event.wheel.y));
            break;

        case SDL_QUIT:
            engine.ShutDown();
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
               
                if (auto p = windowsManager->GetWindows().find(event.window.windowID); p != windowsManager->GetWindows().end())
                {
                    windowsManager->RemoveWindow(event.window.windowID);
                    GENGINE_CORE_INFO("Manager Size {}", windowsManager->GetWindows().size());

                    auto& numWindows = windowsManager->GetNumOfWindows();
                    if (--numWindows == 0) {
                        ShutDown();
                        GENGINE_CORE_INFO("ShutDown!");
                 
                        break;
                    }

                }
            }

            else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                auto new_width = event.window.data1;
                auto new_height = event.window.data2;
                if (auto p = windowsManager->GetWindows().find(event.window.windowID); p != windowsManager->GetWindows().end())
                {
                    p->second->OnResize(new_width, new_height);
                    GENGINE_CORE_INFO("Window with title {} has been resized to ({}, {})", p->second->GetTitle(), new_width, new_height);
                }
            }
         
            break;

      




        }
    }


    void InputManager::SetRelativeMouseMode(bool value)
    {
        const SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
        SDL_SetRelativeMouseMode(set);

        m_InputState.m_Mouse.m_IsRelative = value;
    }


    float InputManager::Filter1D(int input)
    {
        // A value < dead zone is interpreted as 0%
        const int deadZone = 250;
        // A value > max value is interpreted as 100%
        const int maxValue = 30000;

        float retVal = 0.0f;

        // Take absolute value of input
        const int absValue = input > 0 ? input : -input;
        // Ignore input within dead zone
        if (absValue > deadZone)
        {
            // Compute fractional value between dead zone and max value
            retVal = static_cast<float>(absValue - deadZone) /
                (maxValue - deadZone);
            // Make sure sign matches original value
            retVal = input > 0 ? retVal : -1.0f * retVal;
            // Clamp between -1.0f and 1.0f
            retVal = Math::Clamp(retVal, -1.0f, 1.0f);
        }

        return retVal;
    }


    Vector2 InputManager::Filter2D(int inputX, int inputY)
    {
        const float deadZone = 8000.0f;
        const float maxValue = 30000.0f;

        // Make into 2D vector
        Vector2 dir;
        dir.x = static_cast<float>(inputX);
        dir.y = static_cast<float>(inputY);

        const float length = dir.Length();

        // If length < deadZone, should be no input
        if (length < deadZone)
        {
            //dir = Vector2::Zero;
            dir = Vector2{0.f, 0.f};
        }
        else
        {
            // Calculate fractional value between
            // dead zone and max value circles
            float f = (length - deadZone) / (maxValue - deadZone);
            // Clamp f between 0.0f and 1.0f
            f = Math::Clamp(f, 0.0f, 1.0f);
            // Normalize the vector, and then scale it to the
            // fractional value
            dir *= f / length;
        }

        return dir;
    }


}