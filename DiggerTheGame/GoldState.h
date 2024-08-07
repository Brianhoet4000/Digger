#pragma once
#include "GameObject.h"

namespace dae
{
    class GameObject;
    class GoldStateComponent;

    class GoldState
    {
    public:
        virtual ~GoldState() = default;
        virtual void Enter(GoldStateComponent* component) = 0;
        virtual void Update(GoldStateComponent* component, float deltaTime) = 0;
        virtual void Exit(GoldStateComponent* component) = 0;
    };

}