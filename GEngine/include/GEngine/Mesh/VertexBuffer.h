#pragma once
#include"BufferLayout.h"

namespace GEngine::Buffer
{

	class VertexBuffer
	{

	public:

		NONCOPYMOVABLE(VertexBuffer);
		VertexBuffer(unsigned int size);
		VertexBuffer(const std::vector<float>& data, unsigned int size);

		~VertexBuffer();

		void Bind();
		void Unbind();

		const BufferLayout& GetBufferLayout() const { return m_BufferLayout; }

		void SetLayout(const BufferLayout& layout)
		{
			m_BufferLayout = layout;
		}

		void SetData(const std::vector<float>& data);


	private:
		unsigned int m_VertexBufferRef{};
		BufferLayout m_BufferLayout;
	};

}