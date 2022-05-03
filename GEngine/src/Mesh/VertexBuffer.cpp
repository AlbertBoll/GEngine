#include "gepch.h"
#include "Mesh/VertexBuffer.h"

namespace GEngine::Buffer
{
	VertexBuffer::VertexBuffer(unsigned int size)
	{
		glGenBuffers(1, &m_VertexBufferRef);
		ASSERT(m_VertexBufferRef != 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferRef);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}


	VertexBuffer::VertexBuffer(const std::vector<float>& data, unsigned int size)
	{
		glGenBuffers(1, &m_VertexBufferRef);
		ASSERT(m_VertexBufferRef != 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferRef);
		glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
	}


	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBufferRef);
	}


	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferRef);

	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void VertexBuffer::SetData(const std::vector<float>& data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferRef);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size(), data.data());
	}

}

