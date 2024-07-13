#pragma once
#include "Event.h"

namespace dae
{
    class GameObject;

    class Observer
    {
    public:
        virtual ~Observer() {}
        virtual void Notify(Event event, GameObject* gameObject = nullptr) = 0;
    };
}