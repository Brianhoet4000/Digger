#include "ConditionComponent.h"
#include "GameCollisionMngr.h"
#include "HealthComponent.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "ScreenManager.h"
#include "SpawnTimerComponent.h"

dae::ConditionComponent::ConditionComponent(GameObject* owner, std::shared_ptr<GameObject> spawner)
    : BaseComponent(owner)
    , Subject(owner)
    , m_Finished{ false }
{
    m_pSpawner = spawner;
}

void dae::ConditionComponent::Update(float)
{
    for (const auto& player : PlayerManager::GetInstance().GetPlayers())
    {
        if (player->GetComponent<HealthComponent>()->GetAmount() <= -1)
        {
            NotifyObservers(Event::PLAYER_DIED, player.get());
            dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
            dae::SceneManager::GetInstance().SetActiveScene("GameOver");
            return;
        }
    }

    if ((GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
        GameCollisionMngr::GetInstance().GetAllGold().empty()) ||
        (m_pSpawner->GetComponent<dae::SpawnTimerComponent>()->RemainingNumberOfEnemies() == 0 &&
            dae::GameCollisionMngr::GetInstance().GetAllEnemies().empty()))
    {
        m_Finished = true;
    }

    if (m_Finished && !m_DoOnce && dae::ScreenManager::GetInstance().GetCurrentLevel() != 3)
    {
        NotifyObservers(Event::LEVEL_COMPLETED);
        m_DoOnce = true;
    }
}
