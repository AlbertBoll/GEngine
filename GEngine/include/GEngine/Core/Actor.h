#pragma once
#include"Component/Component.h"
#include <Core/Timestep.h>




namespace GEngine
{

	using namespace Component;
	class CameraBase;

	class Actor
	{

	public:
		NONCOPYABLE(Actor);
		Actor() = default;
		Actor(Actor&& other)noexcept;
		Actor& operator=(Actor&& other)noexcept;
		virtual ~Actor()
		{
			std::cout << "Desrtuctor was called!" << std::endl;
		};


		void SetParent(Actor* parent) { m_Parent = parent; }

		Actor* GetParent()const { return m_Parent; }

		std::vector<Actor*>& GetChildrenRef() { return m_ChildrenRef; }

		auto& GetChildren() { return m_Children; }

		std::string GetName()const { return m_Tag.Name; }

		void PrintTransform();

		virtual void Update(Timestep ts){}

		virtual void Render(CameraBase* camera){}


		//Add smarter child pointer
		template<typename child_type, typename = std::enable_if_t<std::is_base_of_v<ScopedPtr<Actor>, child_type>>>
		void Add(child_type&& child)
		{
			child->m_Parent = this;
			m_ChildrenRef.push_back(child.get());
			m_Children.push_back(std::move(child));
			
		}


		//Add smarter children pointers
		template<typename child_type, typename...child_types, typename = std::enable_if_t<std::is_base_of_v<ScopedPtr<Actor>, child_type>>>
		void Add(child_type&& child, child_types&&... children)
		{
			Add(std::move(child));
			Add(std::forward<child_types>(children)...);
		}


		//Add raw child pointer
		template<typename child_type, typename = std::enable_if_t<std::is_base_of_v<Actor, child_type>>>
		void Add(child_type* child)
		{
			child->m_Parent = this;
			ScopedPtr<Actor>temp(child);
			m_ChildrenRef.push_back(child);
			m_Children.push_back(std::move(temp));
		}


		//Add raw children pointers
		template<typename child_type, typename...child_types, typename = std::enable_if_t<std::is_base_of_v<Actor, child_type>>>
		void Add(child_type* child, child_types&&... children)
		{
			Add(child);
			Add(std::forward<child_types>(children)...);
		}


		void Add(const std::initializer_list<Actor*>& children);


		void Remove(Actor* actor);

		template<typename child_type, typename...child_types, typename = std::enable_if_t<std::is_base_of_v<Actor, child_type>>>
		void Remove(child_type* child, child_types&&... children)
		{
			Remove(child);
			Remove(std::forward<child_types>(children)...);
		}


		void Remove(const std::initializer_list<Actor*>& children);

		Mat4 GetWorldTransform() const;

		void ApplyTransform(const Mat4& transform, bool isLocal = true);
		
		void Translate(float x, float y, float z, bool isLocal = true);

		void RotateX(float angle, bool isLocal = true);
		

		void RotateY(float angle, bool isLocal = true);
		

		void RotateZ(float angle, bool isLocal = true);

		void RotateFromArbitaryAxis(const Vec3f& axis, float angle, bool isLocal = true);
		
		void Scale(float scale, bool isLocal = true);

		Vec3f GetWorldPosition() const;

		void SetPosition(const Vec3f& pos);

		void SetPosition(float x, float y, float z);

		void LookAt(const Vec3f& target_position);

		//extract rotation part from 4x4 transform, taking both scaling and shearing into account
		Mat3 GetStrongRotationMatrix()const;

		//Assume no scaling and shearing part
		Mat3 GetWeakRotationMatrix()const;

		Vec3f GetForward()const;

		Vec3f GetRight()const;

		void SetForward(const Vec3f& direction);

		void SetVisibility(bool bVisibility) { m_Visible = bVisibility; }

	protected:
		TransformComponent m_TransformComponent;
		std::vector<ScopedPtr<Actor>> m_Children;

		//Collection of raw children pointer for using its functionality,
		//but not control its life time 
		std::vector<Actor*> m_ChildrenRef;
		Actor* m_Parent{};
		TagComponent m_Tag;
		bool m_Visible{ true };

	};


}
