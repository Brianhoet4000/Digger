// GameObserver.h
#pragma once
#include "Observer.h"
#include <iostream>

#include "HealthComponent.h"
#include "PointComponent.h"

namespace dae
{
    class GameObserver : public Observer
    {
    public:
        void Notify(Event event, GameObject* gameObject) override
        {
            switch (event)
            {
            case Event::SCORE_ADDED_25:
                ScreenManager::GetInstance().IncreasePoint(gameObject, 25);
                break;

            case Event::SCORE_ADDED_250:
                ScreenManager::GetInstance().IncreasePoint(gameObject, 250);
                break;

            case Event::SCORE_ADDED_500:
                ScreenManager::GetInstance().IncreasePoint(gameObject, 500);
                break;

            case Event::PLAYER_DIED:
                std::cout << "Player has died. Game over.\n";
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
