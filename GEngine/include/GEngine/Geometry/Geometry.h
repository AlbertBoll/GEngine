#pragma once
#include <Mesh/IndexBuffer.h>
#include <Mesh/Attribute.h>
#include <unordered_map>
#include <variant>


namespace GEngine
{
	using namespace Buffer;
	class Geometry
	{
	public:
		std::unordered_map<unsigned int, std::variant<Attribute<Vec4f>,
												      Attribute<Vec3f>,
												      Attribute<Vec2f>,
			                                          Attribute<Vec1f>,
												      Attribute<Vec1i>,
			                                          Attribute<Vec2i>, 
			                                          Attribute<Vec3i>,
			                                          Attribute<Vec4i>,
												      Attribute<Mat2>,
												      Attribute<Mat3>,
												      Attribute<Mat4>>> m_Attributes;

		IndexBuffer m_IndexBuffer; // Hold index buffer

		std::vector<unsigned int> m_Buffers; //keep reference of active BufferRef 

		int m_IndicesCount{};
		int m_VertexCount{};
		int m_Binding{ 0 };
		bool b_HasRecursive = false;
		bool b_UseIndexBuffer = false;

	public:

		Geometry() = default;

		//virtual ~Geometry() = default;

		virtual ~Geometry();

	

		void CountVertices();

		void AddIndices(const std::vector<unsigned int>& data);

		auto& GetAttributes() { return m_Attributes; }

		template<typename Attrib>
		void AddAttributes(const Attrib& data);

		template<typename Attrib, typename... Attribs>
		void AddAttributes(const Attrib& data, const Attribs&... rest);

		void ApplyTransform(const Mat4 & transform, unsigned int location = 0, bool bNormal = false);

		void Merge(Geometry* otherGeo);

	};


	template<typename Attrib>
	inline void Geometry::AddAttributes(const Attrib& data)
	{
		if (!data.empty())
		{
			Attribute attribute = Attribute(data);
			m_Buffers.push_back(attribute.GetBufferRef());
			m_Attributes.emplace(m_Binding++, attribute);

			//m_Attributes.insert({ m_Binding++, Attribute(data) });

			if (!b_HasRecursive)
			{
				CountVertices();
				b_HasRecursive = true;
			}

		}
	}
	template<typename Attrib, typename ...Attribs>
	void Geometry::AddAttributes(const Attrib& data, const Attribs & ...rest)
	{
		
		AddAttributes(data);
		AddAttributes(rest...);
		
	}
}
