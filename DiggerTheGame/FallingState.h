#pragma once
#include "GoldState.h"

namespace dae
{

    class FallingState : public dae::GoldState
    {
        virtual void Enter(dae::GoldStateComponent* component) override;
        virtual void Update(dae::GoldStateComponent* component, float deltaTime) override;
        virtual void Exit(dae::GoldStateComponent* component) override;

    private:
        glm::vec2 m_EstimatedPos{ 0,48 };
        glm::vec2 m_StartPos;
        const float m_Speed{ 60.f };
    };

}