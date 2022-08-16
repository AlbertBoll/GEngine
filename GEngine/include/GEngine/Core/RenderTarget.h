#pragma once
#include <Assets/Textures/Texture.h>
#include <Math/Math.h>



namespace GEngine
{
	//using namespace GEngine::Asset;
	//using namespace GEngine::Math;

	enum class RenderTargetTextureFormat
	{
		None = 0,
		//Color
		RGBA8,
		RED_INTEGER,

		DEPTH24STENCIL8,

		//Default
		Depth = DEPTH24STENCIL8
	};

	struct RenderTargetTextureSpecification
	{
		RenderTargetTextureSpecification() = default;
		RenderTargetTextureSpecification(RenderTargetTextureFormat format): TextureFormat(format){}

		RenderTargetTextureFormat TextureFormat = RenderTargetTextureFormat::None;

	};

	struct RenderTargetAttachmentSpecification
	{
		RenderTargetAttachmentSpecification() = default;
		RenderTargetAttachmentSpecification(const std::initializer_list<RenderTargetTextureSpecification>& attachments): Attachments(attachments){}

		std::vector<RenderTargetTextureSpecification> Attachments;
	};

	struct RenderTargetSpecification
	{
		uint32_t Width = 0, Height = 0;
		uint32_t Samples = 4;
		RenderTargetAttachmentSpecification Attachments;

		bool SwapChainTarget = false;
	};

	class RenderTarget
	{
		
	public:
		RenderTarget(const RenderTargetSpecification& spec);

		RenderTarget(const Math::Vec2f& resolution = { 512.f, 512.f });
		//RenderTarget(const Math::Vec2f& resolution = { 512.f, 512.f }, Asset::Texture* tex = nullptr);
		RenderTarget(int x_res, int y_res);

		~RenderTarget();
		

		[[nodiscard]] int GetWidth() const { return m_Width; }
		[[nodiscard]] int GetHeight() const { return m_Height; }
		[[nodiscard]] int GetFrameBufferID() const { return m_FrameBufferID; }
		[[nodiscard]] int GetScreenFrameBufferID() const { return m_ScreenFrameBufferID; }
		[[nodiscard]] int GetRenderBufferID() const { return m_RenderBufferID; }
		//[[nodiscard]] uint64_t GetTargetTextureID() const { return m_Texture->GetTextureID(); }
		[[nodiscard]] uint64_t GetColorAttachmentID() const { return m_ColorAttachmentID; }
		//[[nodiscard]] Asset::Texture* GetTexture() const { return m_Texture; }

		[[nodiscard]] uint64_t GetScreenAttachmentID() const { return m_ScreenColorAttachmentID; }

		void Invalidate();

		void _Invalidate();

		void InvalidatePostProcessing();

		void Bind(unsigned int ID) const;

		void BindFrameBuffer(unsigned int FrameBufferID, unsigned int target)const;

		void BindRenderBuffer()const;

		void BindAndBlitToScreen();

		int ReadPixel(uint32_t attachmentIndex, int x, int y);

		

		void UnBind() const;

		void RenderSize(const Math::Vec2f& resolution = { 512, 512 });

		unsigned int& GetSamples() { return m_Samples; }

		void OnResize(uint32_t width, uint32_t height);

		bool constexpr IsMultiSampled()const { return m_Samples > 1; }

	private:
	
		//Asset::Texture* m_Texture{};
		int m_Width{};
		int m_Height{};
		unsigned int m_Samples = 4;
		unsigned int m_FrameBufferID{};
		unsigned int m_RenderBufferID{};
		unsigned int m_ColorAttachmentID{};
		unsigned int m_ScreenFrameBufferID{};
		unsigned int m_ScreenColorAttachmentID{};

		std::vector<RenderTargetTextureSpecification> m_ColorAttachmentSpecifications;
		RenderTargetSpecification m_Specification;
		std::vector<uint32_t> m_ColorAttachments;
		//uint32_t m_DepthAttachment = 0;
	
	};
}

