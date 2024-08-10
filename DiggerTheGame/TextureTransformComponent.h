#pragma once
#include "BaseComponent.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "GameObject.h"

namespace dae
{

    class TextureTransformComponent : public dae::BaseComponent
    {

    public:

        TextureTransformComponent(GameObject* owner)
            : BaseComponent(owner), m_Rotation(0.0f), m_FlipX(false), m_FlipY(false)
        {
        }
        virtual ~TextureTransformComponent() override = default;
        TextureTransformComponent(const TextureTransformComponent& other) = delete;
        TextureTransformComponent(TextureTransformComponent&& other) = delete;
        TextureTransformComponent& operator=(const TextureTransformComponent& other) = delete;
        TextureTransformComponent& operator=(TextureTransformComponent&& other) = delete;

        //void Update(float deltaTime) override;

        void Render() const
        {
            if (const auto& textureComp = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>())
            {
                dae::Renderer::GetInstance().RenderTexture(
                    *textureComp->GetTexture(),
                    GetOwnerBaseComp()->GetWorldPosition().x,
                    GetOwnerBaseComp()->GetWorldPosition().y,
                    m_Rotation,
                    m_FlipX,
                    m_FlipY
                );
            }
        }

        void SetRotation(float angle)
        {
            m_Rotation = angle;
        }

        void SetFlip(bool flipX, bool flipY)
        {
            m_FlipX = flipX;
            m_FlipY = flipY;
        }

    private:
        bool m_FlipX;
        bool m_FlipY;
        float m_Rotation;
    };

}