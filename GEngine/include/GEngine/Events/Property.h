#pragma once
#include "Graphics/Texture.h"

#define Setter(member) void SetProperty(const decltype(member)& p){\
std::cout << "Property changes to "<< p.m_Property<<std::endl;\
									 member = p;\
}\

#define Getter(member) decltype(member)::PropertyType Get_##member()const{\
							return member;\
}\
                    
#define GetterAndSetter(member) Getter(member);\
                                Setter(member);\
							


namespace GEngine
{
	template<typename T>
	class Property
	{
		
	public:
	
		using PropertyType = T;

		T m_Property{};


		Signal<void(const Property&)> m_PropertySignal;

		Property(const T& property) : m_Property{ property } {}

		Property() = default;

		Property(const Property& other)
		{
			m_Property = other.m_Property;
		}

		Property& operator = (const Property& other)
		{
			if (m_Property != other.m_Property)
			{
				m_Property = other.m_Property;
				m_PropertySignal(*this);
			}

			return *this;
		}

		operator T()const { return m_Property; }

		friend std::ostream& operator<<(std::ostream& os, const Property& m){ os << m.m_Property; return os; }
	};



}
 