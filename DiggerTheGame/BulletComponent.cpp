#include "BulletComponent.h"

#include <memory>
#include <glm/vec2.hpp>

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "ScreenManager.h"
#include "TextureComponent.h"


dae::BulletComponent::BulletComponent(dae::GameObject* owner, glm::vec2 vel, int amountOfBounces)
	:BaseComponent(owner)
	,m_vel{vel}
	,m_Bounce{0}
	,m_AmountOfBounce{amountOfBounces}
	,m_Speed{75.f}
{
	
}

void dae::BulletComponent::Update(float deltaTime)
{
	const auto pColliderBullet = GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>();

	if ((dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(pColliderBullet) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(pColliderBullet)) && m_Bounce < m_AmountOfBounce)
	{
		m_vel = -m_vel;
		++m_Bounce;
	}
	else if((dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(pColliderBullet) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(pColliderBullet)) && m_Bounce >= m_AmountOfBounce)
	{
		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	//If in versus mode
	const auto secondPlayerEnemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithSecondPlayerVersus(pColliderBullet);
	if(secondPlayerEnemy != nullptr)
	{
		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);

		secondPlayerEnemy->GetOwnerBaseComp()->GetComponent<HealthComponent>()->DecreaseAmount(1);
		secondPlayerEnemy->GetOwnerBaseComp()->GetComponent<PointComponent>()->SetAmount(0);

		const auto& scene = dae::SceneManager::GetInstance().GetActiveScene();

		const auto& points = dae::ScreenManager::GetInstance().GetGameObjectInScene(*scene, "PlayerTwoPoints");
		points->GetComponent<TextComponent>()->SetText(std::to_string(secondPlayerEnemy->GetOwnerBaseComp()->GetComponent<PointComponent>()->GetAmount()));

		dae::ScreenManager::GetInstance().ProceedNextLevel();
		return;
	}

	//Enemies
	const auto enemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithEnemiesComponent(pColliderBullet);
	if (enemy != nullptr)
	{
		enemy->GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveEnemyBox(enemy->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());

		GetOwnerBaseComp()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	const auto newPos = GetOwnerBaseComp()->GetRelativePosition() + m_vel * m_Speed * deltaTime;
	GetOwnerBaseComp()->SetRelativePosition(newPos);

}
