#pragma once
#include "Texture.h"
#include <Math/Math.h>



namespace GEngine::Asset
{
    using namespace Math;

    class TextTexture : public Texture
    {

    public:
        TextTexture(const std::string& text, int pointSize = 24,
            const Vec3f& color = { 0.0f, 0.0f, 1.0f },
            const std::string& fileName = "../GraphicEngine/Font/Carlito-Regular.ttf");
    };
}
