#pragma once
#include "BaseComponent.h"


namespace dae
{
    class GameObject;

    class GetOverlappedPlayer : public BaseComponent
    {
    public:
        GetOverlappedPlayer(GameObject* owner)
	        :BaseComponent(owner)
        {}

        void SetPickedUpPlayer(GameObject* player) { m_pOverlappedPlayer = player; }
        GameObject* GetPickedUpPlayer() const { return m_pOverlappedPlayer; }

    private:
        GameObject* m_pOverlappedPlayer = nullptr;
    };
}
