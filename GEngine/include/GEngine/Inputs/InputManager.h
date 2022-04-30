#pragma once

//#include "sdl2/SDL.h"
#include "../Core/KeyCodes.h"
#include "../Core/ControllerCodes.h"
#include "../Math/Math.h"


#define GENGINE_MAX_KEYCODES 512
#define GENGINE_BUTTON(x) (1 << ((x)-1))
#define GENGINE_CONTROLLER_BUTTON_MAX 21



namespace GEngine
{
	using namespace Math;
	using namespace Key;
	using namespace Controller;

	typedef SDL_Event GEngineEvent;
	typedef SDL_EventType EventType;
	typedef SDL_GameController GENGINE_GameController;

	enum class ButtonState
	{
		None,
		Pressed,
		Released,
		Held
	};


	//Helper for keyboard input
	class KeyboardState
	{
	public:
		ButtonState GetKeyState(GEngineKeyCode keyCode)const;
		bool IsKeyHold(GEngineKeyCode keyCode)const { return GetKeyState(keyCode) == ButtonState::Held; };
		bool IsKeyPressed(GEngineKeyCode keyCode)const { return GetKeyState(keyCode) == ButtonState::Pressed; };
		bool IsKeyReleased(GEngineKeyCode keyCode)const { return GetKeyState(keyCode) == ButtonState::Released; };

	private:
		friend class InputManager;
		const uint8_t* m_CurrentState;
		uint8_t m_PreviousState[GENGINE_MAX_KEYCODES];
	};


	//Helper for mouse input
	class MouseState
	{

	public:
		const Vector2& GetPosition() const { return m_MousePos; }
		const Vector2& GetScrollWheel() const { return m_ScrollWheel; }
		void SetMouseRelative(bool new_relative) { m_IsRelative = new_relative; }
		bool GetButtonValue(int button) const;
		ButtonState GetButtonState(int button) const;
		bool isButtonPressed(int button) const { return GetButtonState(button) == ButtonState::Pressed; }
		bool isButtonHeld(int button) const { return GetButtonState(button) == ButtonState::Held; }
		bool isButtonReleased(int button) const { return GetButtonState(button) == ButtonState::Released; }

	private:
		friend class InputManager;
		Vector2 m_MousePos;
		Vector2 m_ScrollWheel;
		uint32_t m_CurrentButtons;
		uint32_t m_PreviousButtons;

		//Are we in relative mouse mode
		bool m_IsRelative;
	};

	//helper for controller input
	class ControllerState
	{

	public:
		bool GetButtonValue(GEngineControllerCode button) const;
		ButtonState GetButtonState(GEngineControllerCode button) const;

		const Vector2& GetLeftStick() const { return m_LeftStick; }
		const Vector2& GetRightStick() const { return m_RightStick; }
		float GetLeftTrigger() const { return m_LeftTrigger; }
		float GetRightTrigger() const { return m_RightTrigger; }

		bool IsControllerConnected() const { return m_IsConnected; }

		bool isButtonPressed(GEngineControllerCode button) const { return GetButtonState(button) == ButtonState::Pressed; }
		bool isButtonHeld(GEngineControllerCode button) const { return GetButtonState(button) == ButtonState::Held; }
		bool isButtonReleased(GEngineControllerCode button) const { return GetButtonState(button) == ButtonState::Released; }


	private:

		friend class InputManager;
		uint8_t m_CurrentButtons[GENGINE_CONTROLLER_BUTTON_MAX];
		uint8_t m_PreviousButtons[GENGINE_CONTROLLER_BUTTON_MAX];

		Vector2 m_LeftStick;
		Vector2 m_RightStick;

		float m_LeftTrigger;
		float m_RightTrigger;

		//Is controller connected
		bool m_IsConnected;

	};


	struct InputState
	{
		KeyboardState m_Keyboard;
		MouseState m_Mouse;
		ControllerState m_Controller;
	};


	class InputManager
	{

	public:
		void Initialize();
		void ShutDown();

		// Called right before Events loop
		void PrepareForUpdate();

		// Called after Events loop
		void Update();

		// Called to process an event 
		void ProcessEvent(GEngineEvent& event);

		const InputState& GetInputState() const { return m_InputState; }

		void SetRelativeMouseMode(bool value);

	private:
		float Filter1D(int input);
		Vector2 Filter2D(int inputX, int inputY);


	private:
		InputState m_InputState;
		GENGINE_GameController* m_GameController{};

	};

}