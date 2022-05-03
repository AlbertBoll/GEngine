#pragma once
#include "Core/Assert.h"

namespace GEngine::Buffer
{

	enum class AttributeType : uint8_t
	{
		None,
		Int,
		Vec2i,
		Vec3i,
		Vec4i,
		Float,
		Vec2f,
		Vec3f,
		Vec4f,
		Mat2,
		Mat3,
		Mat4,
		Bool
	};



	static uint32_t AttributeTypeSize(AttributeType type)
	{
		switch (type)
		{
		case AttributeType::Bool:  return sizeof(bool);       break;
		case AttributeType::Float: return sizeof(float);      break;
		case AttributeType::Vec2f: return sizeof(float) * 2;  break;
		case AttributeType::Vec3f: return sizeof(float) * 3;  break;
		case AttributeType::Vec4f: return sizeof(float) * 4;  break;
		case AttributeType::Int:   return sizeof(int);        break;
		case AttributeType::Vec2i: return sizeof(int) * 2;    break;
		case AttributeType::Vec3i: return sizeof(int) * 3;    break;
		case AttributeType::Vec4i: return sizeof(int) * 4;    break;
		case AttributeType::Mat2:  return sizeof(float) * 4;  break;
		case AttributeType::Mat3:  return sizeof(float) * 9;  break;
		case AttributeType::Mat4:  return sizeof(float) * 16; break;

		}


		ASSERT(false, "Unknown Attribute type");
		return 0;
	}


	struct Attribute
	{
		AttributeType m_Type;
		std::string m_Name;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_Normalized;

		Attribute(AttributeType type, const std::string& name, bool normalized = false) : m_Type(type), m_Name(name), m_Size(AttributeTypeSize(type)), m_Offset(0),  m_Normalized(normalized){}

		uint32_t GetComponentCount()const
		{
			switch (m_Type)
			{
				case AttributeType::Bool:  return 1;
				case AttributeType::Float: return 1;
				case AttributeType::Vec2f: return 2;
				case AttributeType::Vec3f: return 3;
				case AttributeType::Vec4f: return 4;
				case AttributeType::Int:   return 1;
				case AttributeType::Vec2i: return 2;
				case AttributeType::Vec3i: return 3;
				case AttributeType::Vec4i: return 4;
				case AttributeType::Mat2:  return 2;
				case AttributeType::Mat3:  return 3;
				case AttributeType::Mat4:  return 4;
			}

			ASSERT(false, "Unknown Attribute type");
			return 0;
		}

	};


	class BufferLayout
	{
		using iterator = std::vector<Attribute>::iterator;
		using const_iterator = std::vector<Attribute>::const_iterator;

	public:

		BufferLayout() = default;

		template<typename T, typename...Args>
		BufferLayout(const T& attribute, Args&&... args) : BufferLayout(std::forward<Args>(args)...)
		{
			m_Attributes.push_back(attribute);
		}

		BufferLayout(const std::initializer_list<Attribute>& attributes) : m_Attributes(attributes)
		{

			CalculateOffsetsAndStride();
		}

		const std::vector<Attribute>& GetAttributes()const { return m_Attributes; }

		template<typename T, typename...Args>
		void AddAttributes(const T& att, Args&& ... atts)
		{

			m_Attributes.push_back(att);
			AddAttributes(std::forward<Args>(atts)...);

		}

		void AddAttributes(const Attribute& att)
		{
			m_Attributes.push_back(att);
			CalculateOffsetsAndStride();

		}

		void AddAttributes(const std::initializer_list<Attribute>& attributes)
		{
			for (auto& att : attributes)
			{
				m_Attributes.push_back(att);
			}

			CalculateOffsetsAndStride();

		}

		iterator begin() { return m_Attributes.begin(); }
		iterator end() { return m_Attributes.end(); }
		const_iterator begin() const { return m_Attributes.begin(); }
		const_iterator end()const { return m_Attributes.end(); }

		uint32_t GetStride() const { return m_Stride; }


	private:
		void CalculateOffsetsAndStride();


	private:
		std::vector<Attribute>m_Attributes;
		uint32_t m_Stride{};
	};


}


