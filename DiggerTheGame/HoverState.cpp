#include "HoverState.h"
#include "GoldStateComponent.h"

void dae::HoverState::Enter(dae::GoldStateComponent*)
{
	m_Countdownvalue = m_Startvalue;
}

void dae::HoverState::Update(dae::GoldStateComponent* component, float deltaTime)
{
	m_Countdownvalue -= 1 * deltaTime;

	if(m_Countdownvalue <= 0)
	{
		component->ChangeState(component->GetFallingState());
		return;
	}
}

void dae::HoverState::Exit(dae::GoldStateComponent*)
{
}
