#include "gepch.h"
#include "Mesh/BufferLayout.h"

namespace GEngine::Buffer
{
	void BufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		uint16_t offset = 0;
		for (auto& attribute : m_Attributes)
		{
			m_Stride += attribute.m_Size;
			attribute.m_Offset = offset;
			offset += attribute.m_Size;
		}
	}

}