#pragma once
#include <memory>
#include <vector>
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "GameObserver.h" 

namespace dae
{
    class GameObject;

    class PlayerManager final
    {
    public:

        ~PlayerManager() = default;
        PlayerManager(const PlayerManager&) = delete;
        PlayerManager& operator=(const PlayerManager&) = delete;
        PlayerManager(PlayerManager&&) = default;
        PlayerManager& operator=(PlayerManager&&) = default;

        static PlayerManager& GetInstance()
        {
            static PlayerManager instance;
            return instance;
        }

        void AddPlayer(const std::shared_ptr<dae::GameObject>& player)
        {
            m_Players.push_back(player);
        }

        void RemovePlayer(const std::shared_ptr<dae::GameObject>& player)
        {
            m_Players.erase(std::remove(m_Players.begin(), m_Players.end(), player), m_Players.end());
        }

        void RemoveAllPlayers()
        {
            m_Players.clear();
        }

        void CreatePlayers(dae::Scene& scene, bool coop, bool versus = false)
        {
            const auto& PGameObserver = std::make_shared<dae::GameObserver>();

        	const auto& pPlayer_01 = std::make_shared<PlayerOne>(scene, PGameObserver);
            AddPlayer(pPlayer_01->ReturnPlayer());

            if (coop && !versus)
            {
                const auto& pPlayer_02 = std::make_shared<PlayerTwo>(scene, PGameObserver, true);
                AddPlayer(pPlayer_02->ReturnPlayer());
            }
            else if (coop && versus)
            {
                const auto& pPlayer_02 = std::make_shared<PlayerTwo>(scene, PGameObserver, false);
                AddPlayer(pPlayer_02->ReturnPlayer());
            }
        }

        std::vector<std::shared_ptr<dae::GameObject>> GetPlayers() { return m_Players; }

    private:
        PlayerManager() = default;

        std::vector<std::shared_ptr<dae::GameObject>> m_Players;
    };

}