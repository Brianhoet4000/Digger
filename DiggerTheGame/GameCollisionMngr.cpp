#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GetOverlappedPlayer.h"
#include "GoldStateComponent.h"
#include "HobbinComponent.h"
#include "PlayerManager.h"
#include "PointComponent.h"
#include "ScreenManager.h"
#include "ServiceLocator.h"

namespace dae
{
    class GoldStateComponent;

    void dae::GameCollisionMngr::AddCollisionBox(dae::GameObject* owner, GameCollisionComponent* box)
    {
        m_pCollisonBoxes.push_back(box);

        //Check which tag
        {
            if (owner->GetTag() == "Gold")
            {
                m_pGoldBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Emerald")
            {
                m_pEmeraldBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Break")
            {
                m_pDirtBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Wall")
            {
                m_pWallBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Bullet")
            {
                m_pBulletBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Enemy")
            {
                m_pEnemies.push_back(box);
            }
            else if (owner->GetTag() == "Player_01")
            {
                m_pFirstPlayer = box;
            }
            else if (owner->GetTag() == "Player_02")
            {
                m_pSecondPlayer = box;
            }
        }
    }

    void dae::GameCollisionMngr::RemoveCollisionBox(GameCollisionComponent* box)
    {
        m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveDirtBox(GameCollisionComponent* box)
    {
        RemoveCollisionBox(box);
        m_pDirtBoxes.erase(std::remove(m_pDirtBoxes.begin(), m_pDirtBoxes.end(), box), m_pDirtBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveEmeraldBox(GameCollisionComponent* box)
    {
        RemoveCollisionBox(box);
        m_pEmeraldBoxes.erase(std::remove(m_pEmeraldBoxes.begin(), m_pEmeraldBoxes.end(), box), m_pEmeraldBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveGoldBox(GameCollisionComponent* box)
    {
        RemoveCollisionBox(box);
        m_pGoldBoxes.erase(std::remove(m_pGoldBoxes.begin(), m_pGoldBoxes.end(), box), m_pGoldBoxes.end());
    }
    void GameCollisionMngr::RemoveBulletBox(GameCollisionComponent* box)
    {
        RemoveCollisionBox(box);
        m_pBulletBoxes.erase(std::remove(m_pBulletBoxes.begin(), m_pBulletBoxes.end(), box), m_pBulletBoxes.end());
    }
    void GameCollisionMngr::RemoveFirstPlayerBox(GameCollisionComponent* box)
    {
        m_pFirstPlayer = nullptr;
        RemoveCollisionBox(box);
    }
    void GameCollisionMngr::RemoveSecondPlayerBox(GameCollisionComponent* box)
    {
        m_pSecondPlayer = nullptr;
        RemoveCollisionBox(box);
    }
    void GameCollisionMngr::RemoveEnemyBox(GameCollisionComponent* box)
    {
        RemoveCollisionBox(box);
        m_pEnemies.erase(std::remove(m_pEnemies.begin(), m_pEnemies.end(), box), m_pEnemies.end());
    }

    void GameCollisionMngr::ClearAll()
    {
        m_pCollisonBoxes.clear();
        m_pWallBoxes.clear();
        m_pDirtBoxes.clear();
        m_pEmeraldBoxes.clear();
        m_pGoldBoxes.clear();
        m_pBulletBoxes.clear();
        m_pEnemies.clear();
        //m_pFirstPlayer = nullptr;
        //m_pSecondPlayer = nullptr;
    }

    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllWall()
    {
        return m_pWallBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllDirt()
    {
        return m_pDirtBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllEmerald()
    {
        return m_pEmeraldBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllGold()
    {
        return m_pGoldBoxes;
    }
    std::vector<dae::GameCollisionComponent*> GameCollisionMngr::GetAllEnemies()
    {
        return m_pEnemies;
    }

    std::vector<GameCollisionComponent*> GameCollisionMngr::GetAllPlayers() const
    {
        std::vector<dae::GameCollisionComponent*> pPlayers;

        pPlayers.push_back(m_pFirstPlayer);


        if (m_pSecondPlayer != nullptr)
        {
            if (!m_pSecondPlayer->GetIsVersus())
            {
                pPlayers.push_back(m_pSecondPlayer);
            }
        }

        return pPlayers;
    }

    bool dae::GameCollisionMngr::CheckForCollision(const GameCollisionComponent* box) const
    {
        for (const auto& otherBox : m_pCollisonBoxes)
        {
            if (otherBox == box)
                continue;

            if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
            {
                return true;
            }
        }

        return false;


    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForCollisionComponent(const GameCollisionComponent* box) const
    {
        for (const auto& otherBox : m_pCollisonBoxes)
        {
            if (otherBox == box)
                continue;

            if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
            {
                return otherBox;
            }
        }
        return nullptr;
    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForGoldCollisionComponent(const GameCollisionComponent* box) const
    {
        if (!m_pGoldBoxes.empty())
        {
            for (const auto& otherBox : m_pGoldBoxes)
            {
                if (otherBox == box)
                    continue;

                if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
                {
                    return otherBox;
                }
            }
        }
        return nullptr;
    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForDirtCollisionComponent(const GameCollisionComponent* box) const
    {
        if (!m_pDirtBoxes.empty())
        {
            for (const auto& otherBox : m_pDirtBoxes)
            {
                if (otherBox == box)
                    continue;

                if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
                {
                    return otherBox;
                }
            }
        }
        return nullptr;
    }

    GameCollisionComponent* GameCollisionMngr::CheckOverlapWithEnemiesComponent(const GameCollisionComponent* box) const
    {
        if (!m_pEnemies.empty())
        {
            for (const auto& otherBox : m_pEnemies)
            {
                if (otherBox == box)
                    continue;

                if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
                {
                    return otherBox;
                }
            }
        }
        return nullptr;
    }

    GameCollisionComponent* GameCollisionMngr::CheckOverlapWithSecondPlayerVersus(const GameCollisionComponent* box) const
    {
        for (const auto& player : PlayerManager::GetInstance().GetPlayers())
        {
            const auto& pPlayerCollision = player->GetComponent<dae::GameCollisionComponent>();
            if (pPlayerCollision->GetIsVersus())
            {
                if (box->GetCollisionRect().x < pPlayerCollision->GetCollisionRect().x + pPlayerCollision->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > pPlayerCollision->GetCollisionRect().x &&
                    box->GetCollisionRect().y < pPlayerCollision->GetCollisionRect().y + pPlayerCollision->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > pPlayerCollision->GetCollisionRect().y)
                {
                    return pPlayerCollision;
                }
            }
        }
        return nullptr;
    }

    GameCollisionComponent* GameCollisionMngr::CheckOverlapWithFirstPlayer(const GameCollisionComponent* box) const
    {
    	const auto& player = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<GameCollisionComponent>();
		if (player != nullptr)
		{
			if (box->GetCollisionRect().x < player->GetCollisionRect().x + player->GetCollisionRect().w &&
               box->GetCollisionRect().x + box->GetCollisionRect().w > player->GetCollisionRect().x &&
               box->GetCollisionRect().y < player->GetCollisionRect().y + player->GetCollisionRect().h &&
               box->GetCollisionRect().y + box->GetCollisionRect().h > player->GetCollisionRect().y)
			{
				return player;
			}
		}
        
        return nullptr;
    }

    GameCollisionComponent* GameCollisionMngr::CheckOverlapWithPlayers(const GameCollisionComponent* box) const
    {
        for (const auto& player : PlayerManager::GetInstance().GetPlayers())
        {
            if (player == nullptr) return nullptr;

            const auto& PlayerBox = player->GetComponent<GameCollisionComponent>();

            if (box->GetCollisionRect().x < PlayerBox->GetCollisionRect().x + PlayerBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > PlayerBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < PlayerBox->GetCollisionRect().y + PlayerBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > PlayerBox->GetCollisionRect().y)
            {
                return PlayerBox;
            }
        }
       
        return nullptr;
    }

    bool GameCollisionMngr::CheckOverlapWithPlayersBool(const GameCollisionComponent* box) const
    {
        for (const auto& player : PlayerManager::GetInstance().GetPlayers())
        {
            if (player == nullptr) return false;
            if (player->ReturnDeleting()) return false;

            const auto& PlayerBox = player->GetComponent<GameCollisionComponent>();

            if (box->GetCollisionRect().x < PlayerBox->GetCollisionRect().x + PlayerBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > PlayerBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < PlayerBox->GetCollisionRect().y + PlayerBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > PlayerBox->GetCollisionRect().y)
            {
                return true;
            }
        }

        return false;
    }

    bool GameCollisionMngr::CheckOverlapWithEnemies(const GameCollisionComponent* box) const
    {
        if (!m_pEnemies.empty())
        {
            for (const auto& otherbox : m_pEnemies)
            {
                if (otherbox == box)
                    continue;

                if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool dae::GameCollisionMngr::CheckForOverlapDirt(const dae::GameCollisionComponent* box) const
    {
        if (!m_pDirtBoxes.empty())
        {
            for (const auto& otherbox : m_pDirtBoxes)
            {
                if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool GameCollisionMngr::CheckForOverlapWall(const dae::GameCollisionComponent* box) const
    {
        if (!m_pWallBoxes.empty())
        {
            for (const auto& otherbox : m_pWallBoxes)
            {
                if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool dae::GameCollisionMngr::CheckForOverlapBrokenGold(const dae::GameCollisionComponent* box) const
    {
        if (!m_pGoldBoxes.empty())
        {
            for (const auto& otherbox : m_pGoldBoxes)
            {
                if (otherbox->GetOwnerBaseComp()->GetComponent<dae::GoldStateComponent>()->GetCoinsBool())
                {
                    if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                        box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                        box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                        box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void GameCollisionMngr::PlayerLogicBox(dae::GameCollisionComponent* box, glm::vec2 dir)
    {
    	GameCollisionComponent* OverlappedBox = CheckForCollisionComponent(box);

        if (OverlappedBox != nullptr)
        {
            ////Gold Related
            if (OverlappedBox->GetOwnerBaseComp()->GetTag() == "Gold")
            {
                const auto& goldState = OverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GoldStateComponent>();
            
                //Push Gold Left
                if (goldState->GetCurrentState() == goldState->GetIdleState() && !goldState->GetCoinsBool()
                    && dir.x > 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().x + m_Dim, OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().y };
                    OverlappedBox->GetOwnerBaseComp()->SetRelativePosition(newPos);
                }
                //Push Gold Right
                else if (goldState->GetCurrentState() == goldState->GetIdleState() && !goldState->GetCoinsBool()
                    && dir.x < 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().x - m_Dim * 2, OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().y };
                    OverlappedBox->GetOwnerBaseComp()->SetRelativePosition(newPos);
                }
            }
        }
    }

    void GameCollisionMngr::NobbinLogicBox(dae::GameCollisionComponent* box, glm::vec2 dir)
    {
        const auto& OverlappedBox = CheckForCollisionComponent(box);

        //Hobbin
        if (OverlappedBox != nullptr)
        {
            if (box->GetOwnerBaseComp()->GetComponent<dae::HobbinComponent>()->ReturnCharacterState() == dae::HobbinComponent::Hobbin)
            {
                //Dirt block delete
                if (OverlappedBox->GetOwnerBaseComp()->GetTag() == "Break")
                {
                    RemoveDirtBox(OverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
                    OverlappedBox->GetOwnerBaseComp()->MarkTrueForDeleting();
                }
            }

            ////Overlap with emerald pick up
            //if (OverlappedBox->GetOwnerBaseComp()->GetTag() == "Emerald")
            //{
            //    OverlappedBox->GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(box->GetOwnerBaseComp());
            //    sub.NotifyObservers(EMERALD_PICKEDUP, OverlappedBox->GetOwnerBaseComp());
            //}

            //Gold Nobbin
            if (OverlappedBox != nullptr)
            {
                if (OverlappedBox->GetOwnerBaseComp()->GetTag() == "Gold")
                {
                    const auto& goldState = OverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GoldStateComponent>();

                    if (OverlappedBox != nullptr)
                    {
                        ////If Gold not Broken and falls die
                        //if (!goldState->GetCoinsBool() && goldState->GetMoneyBagState() == dae::GoldStateComponent::Falling)
                        //{
                        //    box->GetOwnerBaseComp()->MarkTrueForDeleting();
                        //    RemoveCollisionBox(box);
                        //} 

                        if (OverlappedBox->GetOwnerBaseComp()->GetTag() == "Break")
                        {
                            //Push Gold Left
                            if (goldState->GetCurrentState() == goldState->GetIdleState() && !goldState->GetCoinsBool() && dir.x > 0)
                            {
                                OverlappedBox->GetOwnerBaseComp()->MarkTrueForDeleting();
                                RemoveDirtBox(OverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
                            
                                glm::vec2 newPos = { OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().x + m_Dim, OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().y };
                                OverlappedBox->GetOwnerBaseComp()->SetRelativePosition(newPos);
                            
                            }
                            //Push Gold Right
                            else if (goldState->GetCurrentState() == goldState->GetIdleState() && !goldState->GetCoinsBool() && dir.x < 0)
                            {
                                OverlappedBox->GetOwnerBaseComp()->MarkTrueForDeleting();
                                RemoveDirtBox(OverlappedBox->GetOwnerBaseComp()->GetComponent<dae::GameCollisionComponent>());
                            
                                glm::vec2 newPos = { OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().x - m_Dim, OverlappedBox->GetOwnerBaseComp()->GetRelativePosition().y };
                                OverlappedBox->GetOwnerBaseComp()->SetRelativePosition(newPos);
                            }
                        }
                    }

                    ////If Gold Broken and overlap pick up
                    //if (goldState->GetCoinsBool())
                    //{
                    //    goldState->GetOwnerBaseComp()->GetComponent<GetOverlappedPlayer>()->SetPickedUpPlayer(box->GetOwnerBaseComp());
                    //    sub.NotifyObservers(GOLD_PICKEDUP, goldState->GetOwnerBaseComp());
                    //}
                }
            }
        }
    }

    bool dae::GameCollisionMngr::Raycast(glm::vec2 startpos, glm::vec2 direction,const dae::GameCollisionComponent* box, bool checkDirt) const
    {

        glm::vec2 startPos = startpos;
        startPos.x += box->GetCollisionRect().w / 2.0f;
        startPos.y += box->GetCollisionRect().h / 2.0f;

        glm::vec2 dir = glm::normalize(direction);
        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ 1.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {
            if(boxes == nullptr) return false;;

            if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
                startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
            {
                return false;
            }

        }
        if (checkDirt)
        {
            for (const auto& boxes : m_pDirtBoxes)
            {
                if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                    startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
                    startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                    startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool GameCollisionMngr::AIRaycast(glm::vec2 startpos, glm::vec2 direction, const dae::GameCollisionComponent* box) const
    {
        glm::vec2 startPos = startpos;
        startPos.x += box->GetCollisionRect().w / 2.0f;
        startPos.y += box->GetCollisionRect().h / 2.0f;

        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ -0.5f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {

            if (startPos.x + (direction.x * distance + offset) < boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                startPos.x + direction.x * distance - offset > boxes->GetCollisionRect().x &&
                startPos.y + (direction.y * distance + offset) < boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                startPos.y + direction.y * distance - offset > boxes->GetCollisionRect().y)
            {
                return true;
            }
        }
        for (const auto& boxes : m_pDirtBoxes)
        {
            if (startPos.x + (direction.x * distance + offset) < boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                startPos.x + direction.x * distance - offset > boxes->GetCollisionRect().x &&
                startPos.y + (direction.y * distance + offset) < boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                startPos.y + direction.y * distance - offset > boxes->GetCollisionRect().y)
            {
                return true;
            }
        }
        
        return false;
    }

    bool GameCollisionMngr::AIRaycastUp(glm::vec2 startpos, glm::vec2 direction, const dae::GameCollisionComponent* box) const
    {
        glm::vec2 startPos = startpos;
        startPos.y += box->GetCollisionRect().h / 2.0f;

        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ 2.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {

            if (startPos.y + direction.y * distance - offset >= boxes->GetCollisionRect().y)
            {
                return true;
            }
        }
        for (const auto& boxes : m_pDirtBoxes)
        {
            if (startPos.y + direction.y * distance - offset >= boxes->GetCollisionRect().y)
            {
                return true;
            }
        }

        return false;
    }

    bool GameCollisionMngr::AIRaycastRight(glm::vec2 startpos, glm::vec2 direction, const dae::GameCollisionComponent* box) const
    {
        glm::vec2 startPos = startpos;
        startPos.x += box->GetCollisionRect().w / 2.0f;

        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ 2.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {
            if (startPos.x + direction.x * distance - offset >= boxes->GetCollisionRect().x)
            {
                return true;
            }
        }
        for (const auto& boxes : m_pDirtBoxes)
        {
            if (startPos.x + direction.x * distance - offset >= boxes->GetCollisionRect().x)
            {
                return true;
            }
        }

        return false;
    }

    bool GameCollisionMngr::AIRaycastLeft(glm::vec2 startpos, glm::vec2 direction, const dae::GameCollisionComponent* box) const
    {
        glm::vec2 startPos = startpos;
        startPos.x += box->GetCollisionRect().w / 2.0f;
        startPos.y += box->GetCollisionRect().h / 2.0f;

        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ 2.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {

            if (startPos.x + (direction.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w)
            {
                return true;
            }
        }
        for (const auto& boxes : m_pDirtBoxes)
        {
            if (startPos.x + (direction.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w)
            {
                return true;
            }
        }

        return false;
    }

    bool GameCollisionMngr::AIRaycastDown(glm::vec2 startpos, glm::vec2 direction, const dae::GameCollisionComponent* box) const
    {
        glm::vec2 startPos = startpos;
        startPos.y += box->GetCollisionRect().h / 2.0f;

        float distance = box->GetCollisionRect().w / 2.f;
        const float offset{ 2.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {
            if (startPos.y + (direction.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h)
            {
                return true;
            }
        }
        for (const auto& boxes : m_pDirtBoxes)
        {
            if (startPos.y + (direction.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h)
            {
                return true;
            }
        }

        return false;
    }

}
