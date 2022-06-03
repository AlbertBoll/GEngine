#pragma once

#include <unordered_map>

using namespace GEngine::Asset;


namespace GEngine
{
	//using namespace Graphic;
	//class GEngine::Graphic::Shader;

	enum class LineType
	{
		Connected,
		Loop,
		Segments
	};

	enum class DrawType
	{
		Point,
		Line,
		Surface
	};

	struct PointSetting
	{
		int mode = 0x1B00;
		float pointSize{ 8.0f };
		bool bRoundedPoints = true;
	};

	struct LineSetting
	{
		int mode = 0x0003;
		float lineWidth = 1.0f;
	};

	struct SurfaceSetting
	{
		int mode = 0x0004;
		float lineWidth = 1.0f;
		bool bDoubleSide = true;
		bool bWireFrame = false;
	};

	union PrimitivesSettings
	{
		PointSetting pointSetting;
		LineSetting lineSetting;
		SurfaceSetting surfaceSetting;

		PrimitivesSettings() {}
	};

	struct Setting
	{
		PrimitivesSettings m_PrimitivesSetting;
		int m_TexTarget = 0x0DE1;

	};

	class Material
	{
	protected:
		Setting m_Setting;
		Shader* m_Shader{};
		std::unordered_multimap<unsigned, std::pair<unsigned, unsigned>> m_TextureList;

	public:
		Material() = default;
		virtual ~Material() = default;
		Material(const std::string& vertexFileName, const std::string& fragFileName);

		Material(Material&& other)noexcept;

		Material& operator=(Material&& other)noexcept;

		virtual void SetRenderSettings(const Setting& settings) { m_Setting = settings; }
		std::unordered_multimap<unsigned, std::pair<unsigned, unsigned>>& GetTextureList() { return m_TextureList; }

		[[nodiscard]] GLuint GetShaderRef() const;

		void UseProgram()const;
	

	};

}