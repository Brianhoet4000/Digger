#include "IdleState.h"
#include "GameCollisionMngr.h"

void dae::IdleState::Enter(dae::GoldStateComponent*)
{
}

void dae::IdleState::Update(dae::GoldStateComponent* component, float)
{
	if (dae::GameCollisionMngr::GetInstance().Raycast(component->GetOwnerBaseComp()->GetRelativePosition(),
		glm::vec2 { 0,5 } , component->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>(), true))
	{
		component->ChangeState(component->GetHoverState());
	}
}

void dae::IdleState::Exit(dae::GoldStateComponent*)
{
}
