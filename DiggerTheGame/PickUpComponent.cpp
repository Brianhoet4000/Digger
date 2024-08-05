#include "PickUpComponent.h"

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GetOverlappedPlayer.h"
#include "GoldStateComponent.h"

dae::PickUpComponent::PickUpComponent(dae::GameObject* owner)
	:BaseComponent(owner)
{
}

void dae::PickUpComponent::Update(float)
{
	const auto& playerOverlapped = GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(GetOwnerBaseComp()->GetComponent<GameCollisionComponent>());

	if (playerOverlapped == nullptr) return;

    //Overlap with Emerald pick up
    if (GetOwnerBaseComp()->GetTag() == "Emerald")
    {
        GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(playerOverlapped->GetOwnerBaseComp());
        playerOverlapped->GetOwnerBaseComp()->getSub()->NotifyObservers(EMERALD_PICKEDUP, GetOwnerBaseComp());

        if (!playerOverlapped->GetIsVersus())
        playerOverlapped->GetOwnerBaseComp()->getSub()->NotifyObservers(LEVEL_COMPLETED);
    }
    //Overlap with Gold pick up
    else if (GetOwnerBaseComp()->GetTag() == "Gold")
    {
        if (GetOwnerBaseComp()->GetComponent<GoldStateComponent>()->GetCoinsBool())
        {
            GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(playerOverlapped->GetOwnerBaseComp());
            playerOverlapped->GetOwnerBaseComp()->getSub()->NotifyObservers(GOLD_PICKEDUP, GetOwnerBaseComp());

            if(!playerOverlapped->GetIsVersus())
            playerOverlapped->GetOwnerBaseComp()->getSub()->NotifyObservers(LEVEL_COMPLETED);
        }
    }
}
