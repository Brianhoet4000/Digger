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
	if (GetOwnerBaseComp() == nullptr) return;

	if(!m_ResetEstimatedPos)
	{
		m_EstimatedPos = GetOwnerBaseComp()->GetRelativePosition() + glm::vec2{0, 48};
		m_ResetEstimatedPos = true;
	}

	if (!dae::GameCollisionMngr::GetInstance().Raycast(GetOwnerBaseComp()->GetRelativePosition(),
		m_Direction, GetOwnerBaseComp()->GetComponent<GameCollisionComponent>(), true))
	{
		if (GetOwnerBaseComp()->GetRelativePosition().y >= m_EstimatedPos.y - 2.f && !m_Broke && m_MoneyState == Full)
		{
			//Here Coins
			const auto& texture = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>();
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
			const auto& pPlayerCollision = dae::GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
			if (pPlayerCollision != nullptr)
			{
				GetOwnerBaseComp()->MarkTrueForDeleting();
				pPlayerCollision->GetOwnerBaseComp()->getSub()->NotifyObservers(PLAYER_DIED, pPlayerCollision->GetOwnerBaseComp());
				return;
			}
		}

		//Falling
		const glm::vec2 newPos = GetOwnerBaseComp()->GetRelativePosition();
		m_MoneyState = Falling;
		GetOwnerBaseComp()->SetRelativePosition(newPos.x, newPos.y + m_Speed * deltaTime);
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
