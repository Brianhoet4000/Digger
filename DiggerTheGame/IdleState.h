#pragma once
#include <glm/vec2.hpp>
#include "GoldState.h"
#include "GoldStateComponent.h"

namespace dae
{
    class IdleState : public dae::GoldState
    {
        virtual ~IdleState() = default;
        virtual void Enter(dae::GoldStateComponent* component) override;
        virtual void Update(dae::GoldStateComponent* component, float deltaTime) override;
        virtual void Exit(dae::GoldStateComponent* component) override;
    };
}