// GameObserver.h
#pragma once
#include "Observer.h"
#include <iostream>

namespace dae
{
    class GameObserver : public Observer
    {
    public:
        void Notify(Event event) override
        {
            switch (event)
            {
            case Event::PLAYER_DIED:
                std::cout << "Player has died. Game over.\n";
                // Handle player death logic here
                break;
            case Event::LEVEL_COMPLETED:
                std::cout << "Level completed!\n";
                dae::ScreenManager::GetInstance().ProceedNextLevel();
                // Handle level completion logic here
                break;
            default:
                break;
            }
        }
    };
}
