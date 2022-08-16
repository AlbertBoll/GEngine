#pragma once
#include "Core/Entity.h"

namespace GEngine
{

    class Grid: public Entity
    {
        static Geometry* CreateGeometry(float size, int divisions, 
            const Vec3f grid_color, const Vec3f& center_color_x, const Vec3f& center_color_z);

    public:
        Grid(float size = 10.f, int divisions = 10, float line_width = 1.0f, 
             const Vec3f& grid_color = { .2f, .2f, .2f },
             const Vec3f& center_color_x = { .4f, 0.0f, 0.0f }, 
             const Vec3f& center_color_z = { 0.0f, .4f, 0.0f });


        ~Grid() override;
        void Render(CameraBase* camera) override;
    };

}
