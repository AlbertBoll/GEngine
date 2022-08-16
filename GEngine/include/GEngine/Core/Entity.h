#pragma once
#include "Actor.h"
#include <Material/Material.h>
//#include <Geometry/Geometry.h>



namespace GEngine
{
    class Geometry;
    //class Material;

    class Entity: public Actor
    {
       // unsigned int m_Vao{};
        Geometry* m_Geometry{};
        RefPtr<Material> m_Material{};
        //bool bInstanced = false;

    public:

        NONCOPYABLE(Entity);
        Entity();
        Entity(Geometry* geometry, const RefPtr<Material>& material);

        [[nodiscard]] Material* GetMaterial() const { return m_Material.get(); }
        [[nodiscard]] Geometry* GetGeometry() const { return m_Geometry; }

        Entity(Entity&& other)noexcept;

        //Entity& operator = (Entity&& other)noexcept;

        void UpdateRenderSettings() const;

        RenderSetting& GetRenderSetting() { return m_Material->GetRenderSetting(); }
        void SetRenderMode(RenderMode mode);
        
        ~Entity() override;

        void ArraysDraw() const;

        void ElementsDraw() const;

        //To do element instance draw
        void ElementsInstancedDraw() const;

        //To do array instance draw
        void ArraysInstancedDraw() const;

        void BindTextures() const;

        void BindTexture(int TexTarget = 0x0DE1) const
        {
            m_Material->BindTextureUniforms(TexTarget);
        }

        void SetMaterial(const RefPtr<Material>& material)
        {
            m_Material = material;
        }

        void SetGeometry(Geometry* geometry)
        {
            m_Geometry = geometry;
        }

        void UseShaderProgram()const;
        void BindVAO()const;

        void UnBindVAO()const;

        template <typename T>
        void SetUniforms(const std::map<std::string, T>& uniforms)const
        {
            m_Material->SetUniforms(uniforms);
        }


        void Render(CameraBase* camera)override;
    
    };

}