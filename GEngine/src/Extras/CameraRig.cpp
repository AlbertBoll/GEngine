#include "gepch.h"
#include "Extras/CameraRig.h"
//#include <Managers/InputManager.h>
#include <Core/BaseApp.h>
//#include <imguizmo/ImGuizmo.h>

namespace GEngine
{
	static constexpr float m_MaxPitch = Pi / 2.f;

	CameraRig::CameraRig(bool bAttachToControlledActor, float units_per_seconds, float degree_per_seconds): Actor()
	{
		m_RigParams.m_UnitsPerSecond = units_per_seconds;
		m_RigParams.m_DegreesPerSecond = degree_per_seconds;

		if (bAttachToControlledActor)
		{
			m_RigAttachment = new Actor;
			m_RigAttachment->SetParent(this);
			m_RigAttachment->SetTag("Rig Attachment");
			Add(m_RigAttachment);
		}
	
		
	}

	void CameraRig::Attach(Actor* child)
	{
		if (m_RigAttachment)
			m_RigAttachment->Add(child);

		else Add(child);

	}

	void CameraRig::SetYawSpeed(float YawSpeed)
	{
		m_RigParams.m_YawSpeed = YawSpeed;
	}

	void CameraRig::SetPitchSpeed(float PitchSpeed)
	{
		m_RigParams.m_PitchSpeed = PitchSpeed;
	}

	void CameraRig::Reset()
	{
		m_RigParams.m_YawSpeed = 0.f;
		m_RigParams.m_PitchSpeed = 0.f;
		//m_RigParams.m_CurrentPitch = 0.f;
		//m_RigParams.m_CurrentYaw = 0.f;

	}

	void CameraRig::Update(Timestep ts)
	{
		auto& engine = BaseApp::GetEngine();
		auto* input = engine.GetInputManager();
	
		const float moveAmount = m_RigParams.m_UnitsPerSecond * ts;
		const float rotateAmount = m_RigParams.m_DegreesPerSecond * 3.14f / 180.f * ts;

		const auto keyboard = input->GetKeyboardState();
		auto& mouse = input->GetMouseState();

		//if (!ImGuizmo::IsUsing())
		
		if (keyboard.IsKeyHeld(GENGINE_KEY_W)) Translate(0.f, 0.f, -moveAmount);
		if (keyboard.IsKeyHeld(GENGINE_KEY_S)) Translate(0.f, 0.f, moveAmount);
		if (keyboard.IsKeyHeld(GENGINE_KEY_A)) Translate(-moveAmount, 0.f, 0.f);
		if (keyboard.IsKeyHeld(GENGINE_KEY_D)) Translate(moveAmount, 0.f, 0.f);
		if (keyboard.IsKeyHeld(GENGINE_KEY_R)) Translate(0.f, moveAmount, 0.f);
		if (keyboard.IsKeyHeld(GENGINE_KEY_F)) Translate(0.f, -moveAmount, 0.f);

	    if (keyboard.IsKeyPressed(GENGINE_KEY_SPACE)) input->SetRelativeMouseMode(false);
		
		auto& mouseState = BaseApp::GetEngine().GetInputManager()->GetMouseState();
		
		if (mouse.IsRelative())
		{

			int32_t x = mouseState.m_XRel;
			int32_t y = mouseState.m_YRel;

			//GENGINE_CORE_INFO("relative mode Mouse motion - xPos: {}   yPos: {}", x, y);
			

			const int maxMouseSpeed = 750;
			// Rotation/sec at maximum speed
			const float maxYawSpeed = Math::Pi * 8;
			if (x != 0)
			{
				// Convert to ~[-1.0, 1.0]
				m_RigParams.m_YawSpeed = static_cast<float>(-x) / maxMouseSpeed * maxYawSpeed;
			}


			// Compute pitch
			constexpr float maxPitchSpeed = Pi * 5.f;

			//float pitchSpeed = 0.0f;
			if (y != 0)
			{
				// Convert to ~[-1.0, 1.0]
				m_RigParams.m_PitchSpeed = static_cast<float>(-y) / maxMouseSpeed * maxPitchSpeed;
			}

			if (!Math::NearZero(m_RigParams.m_YawSpeed))
			{
				m_RigParams.m_CurrentYaw += ts * m_RigParams.m_YawSpeed;
			
				const float angle = ts * m_RigParams.m_YawSpeed;
				RotateY(angle);
				//GENGINE_CORE_INFO("Yaw: {}", m_RigParams.m_CurrentYaw);
			}

			if (!Math::NearZero(m_RigParams.m_PitchSpeed))
			{
				m_RigParams.m_CurrentPitch += m_RigParams.m_PitchSpeed * ts;

				m_RigParams.m_CurrentPitch = glm::clamp(m_RigParams.m_CurrentPitch, -m_MaxPitch, m_MaxPitch);
				//GENGINE_CORE_INFO("Pitch: {}", m_RigParams.m_CurrentPitch);
				if (m_RigParams.m_CurrentPitch > -m_MaxPitch && m_RigParams.m_CurrentPitch < m_MaxPitch)
				{
					if (m_RigAttachment) m_RigAttachment->RotateX(m_RigParams.m_PitchSpeed * ts);
					else RotateX(m_RigParams.m_PitchSpeed * ts);
				}


			}

			Reset();
		}
		
		else
		{
			if (keyboard.IsKeyHeld(GENGINE_KEY_Q))
			{
				RotateY(rotateAmount);
			}

			if (keyboard.IsKeyHeld(GENGINE_KEY_E))
			{
				RotateY(-rotateAmount);
			}


			if (keyboard.IsKeyHeld(GENGINE_KEY_T))
			{
				if (m_RigAttachment) m_RigAttachment->RotateX(rotateAmount);
				else RotateX(rotateAmount);
			}

			if (keyboard.IsKeyHeld(GENGINE_KEY_G))
			{
				if (m_RigAttachment) m_RigAttachment->RotateX(-rotateAmount);
				else RotateX(-rotateAmount);
			}
		}

		
	
	}
}