#pragma once
#include <glm/vec2.hpp>
#include "GoldState.h"


namespace dae
{
    class IdleState : public dae::GoldState
    {
        virtual void Enter(dae::GoldStateComponent* component) override;
        virtual void Update(dae::GoldStateComponent* component, float deltaTime) override;
        virtual void Exit(dae::GoldStateComponent* component) override;
    };
}