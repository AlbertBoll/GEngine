#include "gepch.h"
#include "Core/Actor.h"

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
		m_Transform = std::move(other.m_Transform);
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
			m_Transform = std::move(other.m_Transform);
			m_Tag = std::move(other.m_Tag);
		}

		return *this;
	}


}