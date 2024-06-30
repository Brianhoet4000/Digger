#include "ConditionSingleCoopComponent.h"

#include <iostream>

#include "EnemySpawner.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PlayerManager.h"
#include "ScreenManager.h"
#include "TextureComponent.h"

dae::ConditionSingleCoopComponent::ConditionSingleCoopComponent(dae::GameObject* owner, std::shared_ptr<dae::GameObject> spawner)
	:BaseComponent(owner)
	,m_Finished{false}
{
	m_pSpawner = spawner;
}

void dae::ConditionSingleCoopComponent::Update(float)
{
	for (const auto& player : PlayerManager::GetInstance().GetPlayers())
	{
		if (player->GetComponent<HealthComponent>()->GetAmount() <= -1)
		{
			dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
			dae::SceneManager::GetInstance().SetActiveScene("GameOver");
			return;
		}
	}
	


	if((GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
		GameCollisionMngr::GetInstance().GetAllGold().empty()) ||
		(m_pSpawner->GetComponent<dae::SpawnTimerComponent>()->RemainingNumberOfEnemies() == 0 
			&& dae::GameCollisionMngr::GetInstance().GetAllEnemies().empty()))
	{
		m_Finished = true;
	}
	
	if(m_Finished && !m_DoOnce && dae::ScreenManager::GetInstance().GetCurrentLevel() != 3)
	{
		dae::ScreenManager::GetInstance().ProceedNextLevel();
		m_DoOnce = true;
	}
}
