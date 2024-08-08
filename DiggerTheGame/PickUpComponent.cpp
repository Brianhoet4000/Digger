#include "PickUpComponent.h"

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GetOverlappedPlayer.h"
#include "GoldStateComponent.h"
#include "SubjectComponent.h"

dae::PickUpComponent::PickUpComponent(dae::GameObject* owner)
	:BaseComponent(owner)
{
}

void dae::PickUpComponent::Update(float)
{
	const auto& playerOverlapped = GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(GetOwnerBaseComp()->GetComponent<GameCollisionComponent>());

	if (playerOverlapped == nullptr) return;
    if (playerOverlapped->GetIsVersus()) return;;

    //Overlap with Emerald pick up
    if (GetOwnerBaseComp()->GetTag() == "Emerald")
    {
        GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(playerOverlapped->GetOwnerBaseComp());
        playerOverlapped->GetOwnerBaseComp()->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(EMERALD_PICKEDUP, GetOwnerBaseComp());

        if (!playerOverlapped->GetIsVersus())
        playerOverlapped->GetOwnerBaseComp()->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(LEVEL_COMPLETED);
        return;
    }
    //Overlap with Gold pick up
    else if (GetOwnerBaseComp()->GetTag() == "Gold")
    {
        if (GetOwnerBaseComp()->GetComponent<GoldStateComponent>()->GetCoinsBool())
        {
            GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(playerOverlapped->GetOwnerBaseComp());
            playerOverlapped->GetOwnerBaseComp()->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(GOLD_PICKEDUP, GetOwnerBaseComp());

            if(!playerOverlapped->GetIsVersus())
            playerOverlapped->GetOwnerBaseComp()->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(LEVEL_COMPLETED);
        }
    }
    else if (GetOwnerBaseComp()->GetTag() == "Break")
    {
        GetOwnerBaseComp()->MarkTrueForDeleting();
    	GameCollisionMngr::GetInstance().RemoveDirtBox(GetOwnerBaseComp()->GetComponent<GameCollisionComponent>());
    }
}
