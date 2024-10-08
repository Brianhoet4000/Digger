﻿#include "FallingState.h"
#include "GameCollisionMngr.h"
#include "GoldStateComponent.h"
#include "SubjectComponent.h"

void dae::FallingState::Enter(dae::GoldStateComponent* component)
{
	m_EstimatedPos = glm::vec2{ component->GetOwnerBaseComp()->GetRelativePosition().x, component->GetOwnerBaseComp()->GetRelativePosition().y + 48.f };
}

void dae::FallingState::Update(dae::GoldStateComponent* component, float deltaTime)
{
	const auto& pPlayerCollision = dae::GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(component->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
	if (pPlayerCollision != nullptr && !component->GetCoinsBool())
	{
		pPlayerCollision->GetOwnerBaseComp()->GetComponent<dae::SubjectComponent>()->GetSubject()->NotifyObservers(dae::PLAYER_DIED, pPlayerCollision->GetOwnerBaseComp());
		return;
	}

	if (!dae::GameCollisionMngr::GetInstance().Raycast(component->GetOwnerBaseComp()->GetRelativePosition(),
		glm::vec2{ 0,5 }, component->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>(), true))
	{
		if (component->GetOwnerBaseComp()->GetRelativePosition().y >= m_EstimatedPos.y - 2.f)
		{
			component->ChangeState(component->GetCoinState());
			return;
		}
		else
		{
			component->ChangeState(component->GetIdleState());
			return;
		}

	}
	const glm::vec2& newPos = component->GetOwnerBaseComp()->GetRelativePosition();
	component->GetOwnerBaseComp()->SetRelativePosition(newPos.x, newPos.y + m_Speed * deltaTime);
}

void dae::FallingState::Exit(dae::GoldStateComponent* )
{
}
