#include "gepch.h"
#include "Core/Actor.h"
#include "Math/Matrix.h"
#include "Core/Log.h"

namespace GEngine
{


	Actor::Actor(Actor&& other) noexcept
	{
	

		m_Children = std::move(other.m_Children);
		m_ChildrenRef = std::move(other.m_ChildrenRef);
		m_Parent = other.m_Parent;
		other.m_Parent = nullptr;
		m_Visible = other.m_Visible;
		other.m_Visible = false;
		m_TransformComponent = std::move(other.m_TransformComponent);
		m_Tag = std::move(other.m_Tag);
	}

	Actor& Actor::operator=(Actor&& other) noexcept
	{
		if (this != &other)
		{
			m_Children = std::move(other.m_Children);
			m_ChildrenRef = std::move(other.m_ChildrenRef);
			delete m_Parent;
			m_Parent = other.m_Parent;
			other.m_Parent = nullptr;
			m_Visible = other.m_Visible;
			other.m_Visible = false;
			m_TransformComponent = std::move(other.m_TransformComponent);
			m_Tag = std::move(other.m_Tag);
		}

		return *this;
	}

	void Actor::PrintTransform()
	{
		
		std::cout << m_TransformComponent.Transform << std::endl;
	}


	void Actor::Add(const std::initializer_list<Actor*>& children)
	{
		for (auto& p : children)
		{
			Add(p);
		}
	}

	void Actor::Remove(Actor* actor) 
	{
		for (size_t i = 0; i < m_ChildrenRef.size(); ++i)
		{
			if (m_ChildrenRef[i] == actor)
			{
				m_ChildrenRef.erase(m_ChildrenRef.begin() + i);
				m_Children.erase(m_Children.begin() + i);
				break;
			}
		}
	}

	void Actor::Remove(const std::initializer_list<Actor*>& children)
	{
		for (auto& p : children) Remove(p);
	}



	Mat4 Actor::GetWorldTransform() const
	{
		auto condition = bool_variant(!m_Parent);

		return std::visit([&](auto has_no_parent)
				{
				if constexpr (has_no_parent)
				{
					return m_TransformComponent.Transform;
				}

				else if constexpr (!has_no_parent)
				{
					return m_Parent->GetWorldTransform() * m_TransformComponent.Transform;
				}
 
			}, condition);
	}


	void Actor::ApplyTransform(const Mat4& transform, bool isLocal)
	{
		auto is_local = bool_variant(isLocal);

		std::visit([&](auto is_local)
			{
				if constexpr (is_local)
					m_TransformComponent.Transform = m_TransformComponent.Transform * transform;

				else if constexpr (!is_local)
					m_TransformComponent.Transform = transform * m_TransformComponent.Transform;
			}, is_local);
		
		
	}


	void Actor::Translate(float x, float y, float z, bool isLocal)
	{
		ApplyTransform(Matrix::MakeTranslation(x, y, z), isLocal);
	}

	void Actor::RotateX(float angle, bool isLocal)
	{
		ApplyTransform(Matrix::MakeRotationX(angle), isLocal);
	}

	void Actor::RotateY(float angle, bool isLocal)
	{
		ApplyTransform(Matrix::MakeRotationY(angle), isLocal);
	}

	void Actor::RotateZ(float angle, bool isLocal)
	{
		ApplyTransform(Matrix::MakeRotationZ(angle), isLocal);
	}

	void Actor::RotateFromArbitaryAxis(const Vec3f& axis, float angle, bool isLocal)
	{
		ApplyTransform(Matrix::MakeRotationFromArbitaryAxis(axis, angle), isLocal);
	}

	void Actor::Scale(float scale, bool isLocal)
	{
		ApplyTransform(Matrix::MakeScale(scale), isLocal);
	}

	Vec3f Actor::GetWorldPosition() const
	{
		auto world_transform = GetWorldTransform();
		return { world_transform[3][0], world_transform[3][1] , world_transform[3][2] };
	}

	void Actor::SetPosition(const Vec3f& pos)
	{

		m_TransformComponent.Transform[3][0] = pos.x;
		m_TransformComponent.Transform[3][1] = pos.y;
		m_TransformComponent.Transform[3][2] = pos.z;
	}


	void Actor::SetPosition(float x, float y, float z)
	{
		m_TransformComponent.Transform[3][0] = x;
		m_TransformComponent.Transform[3][1] = y;
		m_TransformComponent.Transform[3][2] = z;
	}


	void Actor::LookAt(const Vec3f& target_position)
	{
		m_TransformComponent.Transform = Matrix::MakeLookAt(GetWorldPosition(), target_position);
	}

	Mat3 Actor::GetStrongRotationMatrix() const
	{
		Vec3f t, r, s;
		auto world_transform = GetWorldTransform();
		Matrix::DecomposeTransform(world_transform, t, r, s);
		return glm::toMat4(Quat(r));

	}

	Mat3 Actor::GetWeakRotationMatrix() const
	{
		return Mat3(GetWorldTransform());
	}


	Vec3f Actor::GetForward() const
	{
		return GetWeakRotationMatrix() * Vec3f(0.f, 0.f, -1.f);
	}


	Vec3f Actor::GetRight() const
	{
		return GetWeakRotationMatrix() * Vec3f(1.f, 0.f, 0.f);
	}


	void Actor::SetForward(const Vec3f& direction)
	{
		const auto self_pos = GetWorldPosition();
		const auto target_pos = self_pos + direction;
		LookAt(target_pos);
	}


}