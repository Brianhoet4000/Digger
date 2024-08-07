#include "GoldStateComponent.h"
#include "CoinState.h"
#include "FallingState.h"
#include "HoverState.h"
#include "IdleState.h"
#include "GameObject.h"

dae::GoldStateComponent::GoldStateComponent(dae::GameObject* owner)
	: BaseComponent(owner),
	m_IdleState{ std::make_unique<IdleState>() },
	m_HoverState{ std::make_unique<HoverState>() },
	m_FallingState{ std::make_unique<FallingState>() },
	m_CoinState{ std::make_unique<CoinState>() },
	m_CurrentState{ m_IdleState.get() }
{
	m_CurrentState->Enter(this);
}

dae::GoldStateComponent::~GoldStateComponent()
{
	if (m_CurrentState != m_IdleState.get() && m_CurrentState != m_HoverState.get() &&
		m_CurrentState != m_FallingState.get() && m_CurrentState != m_CoinState.get())
	{
		delete m_CurrentState;
		m_CurrentState = nullptr;
	}
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
