#pragma once
#include <glm/vec2.hpp>
#include "GoldState.h"

namespace dae
{

    class HoverState : public dae::GoldState
    {
        virtual void Enter(dae::GoldStateComponent* component) override;
        virtual void Update(dae::GoldStateComponent* component, float deltaTime) override;
        virtual void Exit(dae::GoldStateComponent* component) override;

    private:
        bool m_StartTimer = false;
        bool m_TimerDone = false;
        float m_Startvalue = 1.5f;
        float m_Countdownvalue = 0.f;
    };

}