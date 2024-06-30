#include "AIMovementComponent.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GoldStateComponent.h"
#include "HealthComponent.h"
#include "HobbinComponent.h"
#include "PlayerManager.h"
#include "PointComponent.h"
#include "ScreenManager.h"

dae::AIMovementComponent::AIMovementComponent(dae::GameObject* owner)
	:BaseComponent(owner)
{
	m_pCollision = owner->GetComponent<dae::GameCollisionComponent>();
}

void dae::AIMovementComponent::Update(float deltaTime)
{
	if (GetOwnerBaseComp()->ReturnDeleting()) return;

	const auto& pPlayerCollision = dae::GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
	if (pPlayerCollision != nullptr)
	{
		dae::ScreenManager::GetInstance().PlayerKilledResetLevelAndStats(pPlayerCollision);

		return;
	}

	const auto& pOverlappedBox = dae::GameCollisionMngr::GetInstance().CheckForCollisionComponent(m_pCollision);
	if (pOverlappedBox != nullptr)
	{
		//Gold Related
		if (pOverlappedBox->GetOwnerBaseComp()->GetTag() == "Gold")
		{
			const auto& goldState = pOverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GoldStateComponent>();

			//If Gold not Broken and falls die
			if (!goldState->GetCoinsBool() && goldState->GetMoneyBagState() == dae::GoldStateComponent::Falling)
			{
				GetOwnerBaseComp()->MarkTrueForDeleting();
				dae::GameCollisionMngr::GetInstance().RemoveEnemyBox(m_pCollision);
			}
		}
	}

	const auto& pHobbincomp = GetOwnerBaseComp()->GetComponent<dae::HobbinComponent>();

	if (pHobbincomp->ReturnCharacterState() == HobbinComponent::Nobbin)
	{
		if (m_Horizontal)
		{
			bool left = dae::GameCollisionMngr::GetInstance().AIRaycast(GetOwnerBaseComp()->GetRelativePosition(), m_DirLeft, m_pCollision);
			bool right = dae::GameCollisionMngr::GetInstance().AIRaycast(GetOwnerBaseComp()->GetRelativePosition(), m_DirRight, m_pCollision);


			if (right)
			{
				m_CheckRight = true;
			}
			if (left)
			{
				m_CheckLeft = true;
			}


			if (!m_CheckLeft)
			{
				MoveAI(deltaTime, m_DirLeft);
			}
			else if (!m_CheckRight)
			{
				MoveAI(deltaTime, m_DirRight);
			}
		}
		else if (m_Vertical)
		{
			bool up = dae::GameCollisionMngr::GetInstance().AIRaycast(GetOwnerBaseComp()->GetRelativePosition(), m_DirUp, m_pCollision);
			bool down = dae::GameCollisionMngr::GetInstance().AIRaycast(GetOwnerBaseComp()->GetRelativePosition(), m_DirDown, m_pCollision);

			if (up)
			{
				m_CheckUp = true;
			}
			if (down)
			{
				m_CheckDown = true;
			}

			if (!m_CheckUp)
			{
				MoveAI(deltaTime, m_DirUp);
			}
			else if (!m_CheckDown)
			{
				MoveAI(deltaTime, m_DirDown);
			}
		}

		if (m_CheckLeft && m_CheckRight)
		{
			m_Horizontal = false;
			m_Vertical = true;
		}
		if (m_CheckUp && m_CheckDown)
		{
			m_Horizontal = true;
			m_Vertical = false;
		}

		if (m_CheckLeft && m_CheckRight && m_CheckUp && m_CheckDown)
		{
			m_CheckLeft = false;
			m_CheckRight = false;
			m_CheckUp = false;
			m_CheckDown = false;
		}
	}
	else
	{
		GetClosestPlayer();

		const float offset{ 0.3f };
		const auto& pOverlappedBoxDirtAndEmerald = dae::GameCollisionMngr::GetInstance().CheckForCollisionComponent(m_pCollision);

		if (pOverlappedBoxDirtAndEmerald != nullptr)
		{
			//Dirt block delete
			if (pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->GetTag() == "Break")
			{
				dae::GameCollisionMngr::GetInstance().RemoveDirtBox(pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
				pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->MarkTrueForDeleting();
			}

			//Overlap with emerald pick up
			if (pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->GetTag() == "Emerald")
			{
				dae::GameCollisionMngr::GetInstance().RemoveEmeraldBox(pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
				pOverlappedBoxDirtAndEmerald->GetOwnerBaseComp()->MarkTrueForDeleting();
			}
		}

		if(m_Horizontal)
		{

			if (m_pClosestPlayer->GetRelativePosition().y - offset < GetOwnerBaseComp()->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirUp);
			}
			else if(m_pClosestPlayer->GetRelativePosition().y + offset > GetOwnerBaseComp()->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirDown);
			}

			
			if(m_pClosestPlayer->GetRelativePosition().y <  GetOwnerBaseComp()->GetRelativePosition().y + offset &&
				m_pClosestPlayer->GetRelativePosition().y >  GetOwnerBaseComp()->GetRelativePosition().y - offset)
			{
				m_Vertical = true;
				m_Horizontal = false;
			}
		}
		else if(m_Vertical)
		{

			if (m_pClosestPlayer->GetRelativePosition().x - offset < GetOwnerBaseComp()->GetRelativePosition().x)
			{
				MoveAI(deltaTime, m_DirLeft);
			}
			else if (m_pClosestPlayer->GetRelativePosition().y + offset > GetOwnerBaseComp()->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirRight);
			}

			if (m_pClosestPlayer->GetRelativePosition().x < GetOwnerBaseComp()->GetRelativePosition().x - offset &&
				m_pClosestPlayer->GetRelativePosition().y > GetOwnerBaseComp()->GetRelativePosition().y + offset)
			{
				m_Vertical = false;
				m_Horizontal = true;
			}
		}
	}
}

void dae::AIMovementComponent::MoveAI(float deltaTime, glm::vec2 dir) const
{
	GetOwnerBaseComp()->SetRelativePosition(GetOwnerBaseComp()->GetRelativePosition() + dir * m_Speed * deltaTime);
}

void dae::AIMovementComponent::GetClosestPlayer()
{
	const auto& pPlayers = PlayerManager::GetInstance().GetPlayers();

	if (pPlayers.empty()) return;
	
	float closestdist{ INFINITY };

	for (const auto& player : pPlayers)
	{
		if (player == nullptr) continue;;

		const float dist = glm::distance(player->GetRelativePosition(), GetOwnerBaseComp()->GetRelativePosition());
		if (dist < closestdist)
		{
			closestdist = dist;
			m_pClosestPlayer = player.get();
		}
	}
}
