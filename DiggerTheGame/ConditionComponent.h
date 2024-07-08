// ConditionSingleCoopComponent.h
#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include <memory>

namespace dae
{
    class GameObject;

    class ConditionComponent : public BaseComponent, public Subject
    {
    public:
        ConditionComponent(GameObject* owner, std::shared_ptr<GameObject> spawner);
        void Update(float deltaTime) override;

    private:
        std::shared_ptr<GameObject> m_pSpawner;
        bool m_Finished;
        bool m_DoOnce{ false };
    };
}

