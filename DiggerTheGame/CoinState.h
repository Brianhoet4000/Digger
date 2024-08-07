#pragma once
#include "GoldState.h"

namespace dae
{

    class CoinState : public dae::GoldState
    {
        virtual void Enter(dae::GoldStateComponent* component) override;
        virtual void Update(dae::GoldStateComponent* component, float deltaTime) override;
        virtual void Exit(dae::GoldStateComponent* component) override;
    };

}