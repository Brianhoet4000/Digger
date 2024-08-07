#include "GoldStateComponent.h"

#include "CoinState.h"
#include "CollisionBoxManager.h"
#include "FallingState.h"
#include "IdleState.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HoverState.h"
#include "IdleState.h"
#include "PointComponent.h"
#include "ScreenManager.h"
#include "ServiceLocator.h"
#include "SubjectComponent.h"
#include "TextureComponent.h"

dae::GoldStateComponent::GoldStateComponent(dae::GameObject* owner)
	:BaseComponent(owner),
	m_IdleState{new IdleState()},
	m_HoverState{new HoverState()},
	m_FallingState{new FallingState()},
	m_CoinState{new CoinState()}
{
	m_CurrentState = m_IdleState;
	m_CurrentState->Enter(this);
}

void dae::GoldStateComponent::Update(float deltaTime)
{
	if (GetOwnerBaseComp()->ReturnDeleting()) return;
	if (GetOwnerBaseComp() == nullptr) return;

	m_CurrentState->Update(this, deltaTime);
}

void dae::GoldStateComponent::ChangeState(GoldState* newState)
{
	if (m_CurrentState)
	{
		m_CurrentState->Exit(this);
	}

	m_CurrentState = newState;

	if (m_CurrentState)
	{
		m_CurrentState->Enter(this);
	}
}