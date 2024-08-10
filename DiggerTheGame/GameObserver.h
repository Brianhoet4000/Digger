#pragma once
#include "Observer.h"
#include "ScreenManager.h"
#include "GameCollisionMngr.h"
#include "GetOverlappedPlayer.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpawnTimerComponent.h"
#include "TextComponent.h"

namespace dae
{

    class GameObserver : public Observer
    {
    private:
        void IncreasePoints(GameObject* player, int points)
        {
            Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();
            if (player->GetTag() == "Player_01")
            {
                player->GetComponent<PointComponent>()->IncreaseAmount(points);
                const auto& pointPlayerOnePoints = dae::ScreenManager::GetInstance().GetGameObjectInScene(*scene, "PlayerOnePoints");
                pointPlayerOnePoints->GetComponent<TextComponent>()->SetText(std::to_string(player->GetComponent<PointComponent>()->GetAmount()));
            }
            else if (player->GetTag() == "Player_02")
            {
                player->GetComponent<PointComponent>()->IncreaseAmount(points);
                const auto& pointPlayerTwoPoints = dae::ScreenManager::GetInstance().GetGameObjectInScene(*scene, "PlayerTwoPoints");
                pointPlayerTwoPoints->GetComponent<TextComponent>()->SetText(std::to_string(player->GetComponent<PointComponent>()->GetAmount()));
            }
        }
        void ChangeLives(GameObject* player)
        {
            Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();
            if (player->GetTag() == "Player_01")
            {
                const auto& pointPlayerOnePoints = dae::ScreenManager::GetInstance().GetGameObjectInScene(*scene, "PlayerOneLives");
                pointPlayerOnePoints->GetComponent<TextComponent>()->SetText(std::to_string(player->GetComponent<HealthComponent>()->GetAmount()));
            }
            else if (player->GetTag() == "Player_02")
            {
                const auto& pointPlayerTwoPoints = dae::ScreenManager::GetInstance().GetGameObjectInScene(*scene, "PlayerTwoLives");
                pointPlayerTwoPoints->GetComponent<TextComponent>()->SetText(std::to_string(player->GetComponent<HealthComponent>()->GetAmount()));
            }
        }

    public:
        void Notify(Event event, GameObject* gameObject = nullptr) override
        {
            switch (event)
            {
            case Event::SCORE_ADDED_250:

                IncreasePoints(gameObject, 250);
                break;

            case Event::PLAYER_DIED:

                gameObject->GetComponent<HealthComponent>()->DecreaseAmount(1);

                if (gameObject->GetComponent<HealthComponent>()->GetAmount() <= -1)
                {
                    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
                    dae::SceneManager::GetInstance().SetActiveScene("GameOver");
                    return;
                }

                if (!gameObject->GetComponent<GameCollisionComponent>()->GetIsVersus())
                {
                    dae::GameCollisionMngr::GetInstance().ClearAll();
                    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
                    dae::ScreenManager::GetInstance().CreateGameScreen(*SceneManager::GetInstance().GetActiveScene());
                }
                else
                {
                    gameObject->SetRelativePosition(ScreenManager::GetInstance().GetLevel()->GetSpawnPosition()[1]);
                    ChangeLives(gameObject);
                }

                break;

            case Event::LEVEL_COMPLETED:
                if (GameCollisionMngr::GetInstance().GetAllEmerald().size() <= 0 && GameCollisionMngr::GetInstance().GetAllGold().size() <= 0)
                {
                    dae::ScreenManager::GetInstance().ProceedNextLevel();
                }
                break;

            case Event::LEVEL_COMPLETED_ENEMIES:
                if(gameObject->GetComponent<SpawnTimerComponent>()->RemainingNumberOfEnemies() <= 0 && GameCollisionMngr::GetInstance().GetAllEnemies().size() <= 1)
                {
                    dae::ScreenManager::GetInstance().ProceedNextLevel();
                }

                break;

            case Event::GOLD_PICKEDUP:

                dae::GameCollisionMngr::GetInstance().RemoveGoldBox(gameObject->GetComponent<dae::GameCollisionComponent>());
                IncreasePoints(gameObject->GetComponent<GetOverlappedPlayer>()->GetPickedUpPlayer(), 500);
                gameObject->MarkTrueForDeleting();
                dae::servicelocator::get_sound_system().playSound(1, 5);
                break;

            case Event::EMERALD_PICKEDUP:

                dae::GameCollisionMngr::GetInstance().RemoveEmeraldBox(gameObject->GetComponent<dae::GameCollisionComponent>());
                IncreasePoints(gameObject->GetComponent<GetOverlappedPlayer>()->GetPickedUpPlayer(), 25);
                gameObject->MarkTrueForDeleting();
                dae::servicelocator::get_sound_system().playSound(1, 5);
                break;

            default:
                break;
            }
        }
    };
}
