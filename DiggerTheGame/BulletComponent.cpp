#include "BulletComponent.h"
#include <memory>
#include <glm/vec2.hpp>
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GetOverlappedPlayer.h"
#include "PointComponent.h"
#include "ScreenManager.h"
#include "SubjectComponent.h"
#include "TextureComponent.h"


dae::BulletComponent::BulletComponent(dae::GameObject* owner, glm::vec2 vel, int amountOfBounces, GameObject* ownerOfBullet)
	:BaseComponent(owner)
	,m_Vel{vel}
	,m_Bounce{0}
	,m_AmountOfBounce{amountOfBounces}
	,m_Speed{75.f}
	,m_OwnerOfBullet{ownerOfBullet}
{
	
}

void dae::BulletComponent::Update(float deltaTime)
{
	const auto& pColliderBullet = GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>();

	if ((dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(pColliderBullet) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(pColliderBullet)) && m_Bounce < m_AmountOfBounce)
	{
		m_Vel = -m_Vel;
		++m_Bounce;
	}
	else if((dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(pColliderBullet) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(pColliderBullet)) && m_Bounce >= m_AmountOfBounce)
	{
		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	//If in versus mode
	const auto& secondPlayerEnemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithSecondPlayerVersus(pColliderBullet);
	if(secondPlayerEnemy != nullptr)
	{
		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);

		secondPlayerEnemy->GetOwnerBaseComp()->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(PLAYER_DIED, secondPlayerEnemy->GetOwnerBaseComp());
		return;
	}

	//Enemies
	const auto& enemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithEnemiesComponent(pColliderBullet);
	if (enemy != nullptr)
	{
		m_OwnerOfBullet->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(SCORE_ADDED_250, m_OwnerOfBullet);
		m_OwnerOfBullet->GetComponent<SubjectComponent>()->GetSubject()->NotifyObservers(LEVEL_COMPLETED, enemy->GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->GetPickedUpPlayer());

		enemy->GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveEnemyBox(enemy->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());

		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	const auto& newPos = GetOwnerBaseComp()->GetRelativePosition() + m_Vel * m_Speed * deltaTime;
	GetOwnerBaseComp()->SetRelativePosition(newPos);
}
