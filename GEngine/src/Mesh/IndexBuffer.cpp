#include "gepch.h"
#include "Mesh/IndexBuffer.h"

namespace GEngine::Buffer
{

	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_IndexBufferRef);
		ASSERT(m_IndexBufferRef != 0);
	}


	IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data) : m_Data(data)
	{
		glGenBuffers(1, &m_IndexBufferRef);
		ASSERT(m_IndexBufferRef != 0);
		UploadIndex();
	}

	void IndexBuffer::AddIndexData(const std::vector<unsigned int>& data)
	{
		ASSERT(m_Data.empty());
		m_Data = data;
		UploadIndex();

	}

	void IndexBuffer::UploadIndex()
	{

		ASSERT(m_IndexBufferRef != 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferRef);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Data.size() * sizeof(unsigned int), m_Data.data(), GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferRef);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferRef);
	}


}