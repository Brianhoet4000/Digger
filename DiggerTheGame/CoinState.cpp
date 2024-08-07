#include "CoinState.h"
#include "GameCollisionComponent.h"
#include "GameCollisionMngr.h"
#include "TextureComponent.h"
#include "GoldStateComponent.h"

void dae::CoinState::Enter(dae::GoldStateComponent* component)
{
	const auto& texture = component->GetOwnerBaseComp()->GetComponent<dae::TextureComponent>();
	texture->SetTexture("Sprites/Gold.png");
	component->SetCoinsBool(true);
}

void dae::CoinState::Update(dae::GoldStateComponent* component, float)
{
	if (dae::GameCollisionMngr::GetInstance().Raycast(component->GetOwnerBaseComp()->GetRelativePosition(),
		glm::vec2{ 0,5 }, component->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>(), true))
	{
		component->ChangeState(component->GetFallingState());
		return;
	}
}

void dae::CoinState::Exit(dae::GoldStateComponent*)
{
}
