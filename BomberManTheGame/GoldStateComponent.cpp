#include "GoldStateComponent.h"
#include "CollisionBoxManager.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "ScreenManager.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"

dae::GoldStateComponent::GoldStateComponent(dae::GameObject* owner)
	:BaseComponent(owner)
{
	m_EstimatedPos = glm::vec2{ 0,0 };
	m_Countdownvalue = m_Startvalue;
}

void dae::GoldStateComponent::Update(float deltaTime)
{
	if (m_pOwner == nullptr) return;

	if(!m_ResetEstimatedPos)
	{
		m_EstimatedPos = m_pOwner->GetRelativePosition() + glm::vec2{0, 48};
		m_ResetEstimatedPos = true;
	}

	if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pOwner->GetRelativePosition(),
		m_Direction, m_pOwner->GetComponent<GameCollisionComponent>(), true))
	{
		if (m_pOwner->GetRelativePosition().y >= m_EstimatedPos.y - 2.f && !m_Broke && m_MoneyState == Full)
		{
			//Here Coins
			const auto& texture = m_pOwner->GetComponent<dae::TextureComponent>();
			texture->SetTexture("Sprites/Gold.png");
			m_Broke = true;

			m_TimerDone = true;
			m_Countdownvalue = 0;

			m_MoneyState = Coins;
			dae::servicelocator::get_sound_system().playSound(2, 20);

			return;
		}
		else if(m_MoneyState == Falling)
		{
			if(!m_Broke)
				m_MoneyState = Full;

			if(m_Broke)
				m_MoneyState = Coins;

			return;
		}
		else if (m_MoneyState == Full)
		{
			//Still MoneyBag
			m_ResetEstimatedPos = false;
			m_MoneyState = Full;

			m_TimerDone = false;
			m_Countdownvalue = m_Startvalue;
			m_StartTimer = false;

			return;
		}
		else if(m_MoneyState == Coins)
		{
			m_TimerDone = false;
			return;
		}
	}
	else
	{
		m_StartTimer = true;

		if (m_MoneyState == Coins)
		{
			m_TimerDone = true;
		}
	}

	if (m_TimerDone)
	{
		if (!m_Broke)
		{
			const auto& pPlayerCollision = dae::GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(m_pOwner->GetComponent<dae::GameCollisionComponent>());
			if (pPlayerCollision != nullptr)
			{
				dae::ScreenManager::GetInstance().PlayerKilledResetLevelAndStats(pPlayerCollision);
				return;
			}
		}

		//Falling
		const glm::vec2 newPos = m_pOwner->GetRelativePosition();
		m_MoneyState = Falling;
		m_pOwner->SetRelativePosition(newPos.x, newPos.y + m_Speed * deltaTime);
	}

	if(m_StartTimer)
	{
		m_Countdownvalue -= 1 * deltaTime;

		if(m_Countdownvalue <= 0)
		{
			m_TimerDone = true;
		}
	}

	
}
