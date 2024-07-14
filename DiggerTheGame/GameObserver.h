#pragma once
#include "Observer.h"
#include <iostream>
#include "ScreenManager.h"
#include "GameCollisionMngr.h"
#include "HealthComponent.h"
#include "PointComponent.h"

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

    public:
        void Notify(Event event, GameObject* gameObject) override
        {
            switch (event)
            {
            case Event::SCORE_ADDED_25:
                IncreasePoints(gameObject, 25);
                break;

            case Event::SCORE_ADDED_250:
                IncreasePoints(gameObject, 250);
                break;

            case Event::SCORE_ADDED_500:
                IncreasePoints(gameObject, 500);
                break;

            case Event::PLAYER_DIED:

                gameObject->GetComponent<HealthComponent>()->DecreaseAmount(1);

                dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
                dae::GameCollisionMngr::GetInstance().ClearAll();
                ScreenManager::GetInstance().CreateGameScreen(*SceneManager::GetInstance().GetActiveScene());
                std::cout << "Player has died.\n";
                break;

            case Event::LEVEL_COMPLETED:
                std::cout << "Level completed!\n";
                dae::ScreenManager::GetInstance().ProceedNextLevel();
                break;

            default:
                break;
            }
        }
    };
}
