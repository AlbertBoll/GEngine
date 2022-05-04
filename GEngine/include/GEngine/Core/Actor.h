#pragma once
#include"Component/Component.h"


using namespace GEngine::Component;
namespace GEngine
{
	class Actor
	{

	public:
		NONCOPYABLE(Actor);
		Actor() = default;
		Actor(Actor&& other)noexcept;
		Actor& operator=(Actor&& other)noexcept;
		virtual ~Actor() = default;

		template<typename child_type, typename = std::enable_if_t<std::is_base_of_v<Actor, child_type>>>
		void Add(const child_type& child)
		{

		}

	protected:
		TransformComponent m_Transform;
		std::vector<ScopedPtr<Actor>> m_Children;

		//Collection of raw children pointer for using its functionality,
		//but not control its life time 
		std::vector<Actor*> m_ChildrenRef;
		Actor* m_Parent{};
		TagComponent m_Tag;
		bool m_Visible{ true };

	};


}
