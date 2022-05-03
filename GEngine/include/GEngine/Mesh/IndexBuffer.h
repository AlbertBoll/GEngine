#pragma once

namespace GEngine::Buffer
{

	class IndexBuffer
	{

	public:
		NONCOPYMOVABLE(IndexBuffer);
		IndexBuffer();
		IndexBuffer(const std::vector<unsigned int>& data);
		unsigned int GetBufferRef()const { return m_IndexBufferRef; }

		void AddIndexData(const std::vector<unsigned int>& data);

		void UploadIndex();

		void Bind();
		void Unbind();

		~IndexBuffer();

	private:
		unsigned int m_IndexBufferRef{};
		std::vector<unsigned int> m_Data;

	};
	
}
