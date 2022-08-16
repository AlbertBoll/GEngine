#pragma once
#include "Entity.h"

namespace GEngine
{
    class AAEntity : public Entity
    {
    public:
        AAEntity(Geometry* geometry, const RefPtr<Material>& material): Entity(geometry, material)
        {

        }

        void Render(CameraBase* camera)override;
    };

}