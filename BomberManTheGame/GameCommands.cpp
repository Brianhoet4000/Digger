#include "GameCommands.h"
#include "Bullet.h"
#include "CollisionBoxManager.h"
#include "GameCollisionMngr.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "ShootingDirComponent.h"

GameCommands::DiggerMovement::DiggerMovement(std::shared_ptr<dae::GameObject> owner, const glm::vec2& dir, bool digger)
{
	m_pGameObject = owner;
	m_Dir = dir;
    m_pCollision = m_pGameObject->GetComponent<dae::GameCollisionComponent>();
    m_Digger = digger;
}

void GameCommands::DiggerMovement::Execute(float deltaTime)
{
    if (m_pGameObject->ReturnDeleting()) return;

    glm::vec2 pos = m_pGameObject->GetRelativePosition();

    if (m_Digger) //Single/Coop -> Digger
    {
        //ShootingDir
        {
            auto shootingstate = m_pGameObject->GetComponent<dae::ShootingDirComponent>();

            if (shootingstate == nullptr) return;

            if (m_Dir.x > 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Right);
            }
            if (m_Dir.x < 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Left);
            }
            if (m_Dir.y < 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Up);
            }
            if (m_Dir.y > 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Down);
            }
        }

        dae::GameCollisionMngr::GetInstance().PlayerLogicBox(m_pGameObject->GetComponent<dae::GameCollisionComponent>(), m_Dir);

        if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, false))
            return;
    }
    else //Verus -> Nobbin
    {
        dae::GameCollisionMngr::GetInstance().NobbinLogicBox(m_pGameObject->GetComponent<dae::GameCollisionComponent>(), m_Dir);

    	if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, true))
            return;
       
    }

    pos.x += m_Dir.x * deltaTime;
    pos.y += m_Dir.y * deltaTime;
    
    m_pGameObject->SetRelativePosition(pos);
}

GameCommands::ShootingBullet::ShootingBullet(std::shared_ptr<dae::GameObject> owner,dae::Scene* scene)
{
    m_pGameObject = owner;
    m_Scene = scene;
    m_pBulletTimer = owner->GetComponent<dae::BulletTimerComponent>();
}

void GameCommands::ShootingBullet::Execute(float)
{
    if(GetKeyPressed()) return;
    if (m_pGameObject == nullptr) return;
    if (m_pGameObject->ReturnDeleting()) return;
    if (m_pBulletTimer->ReturnHasShot()) return;

    auto shootingState = m_pGameObject->GetComponent<dae::ShootingDirComponent>();

    if (shootingState == nullptr) return;

    if(shootingState->returnFaceState() == dae::ShootingDirComponent::Right)
    {
        m_Dir = { 1,0 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Left)
    {
        m_Dir = { -1,0 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Up)
    {
        m_Dir = { 0,-1 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Down)
    {
        m_Dir = { 0,1 };
    }

    auto bullet = std::make_shared<dae::Bullet>(m_pGameObject->GetRelativePosition(), m_Dir);
    m_pBulletTimer->SetHasShot(true);
    dae::SceneManager::GetInstance().GetActiveScene()->Add(bullet->ReturnBullet());

    SetKeyPressed(true);
}


GameCommands::SwitchGameMode::SwitchGameMode(std::shared_ptr<dae::GameObject> owner, dae::GameObject* text, dae::ScreenManager::GameMode& currentScreen, dae::ScreenManager* screen)
	:m_pScreen{owner},
    m_pTextMode{text},
    m_CurrentScreen{ currentScreen },
	m_pScreenManager{ screen }
{
}

void GameCommands::SwitchGameMode::Execute(float)
{
    if (GetKeyPressed()) return;

    auto text = m_pTextMode->GetComponent<dae::TextComponent>();

    switch (m_CurrentScreen)
    {
    case 0:
        m_CurrentScreen = dae::ScreenManager::GameMode::Coop;
        text->SetText("Coop");
        break;

    case 1:
        m_CurrentScreen = dae::ScreenManager::GameMode::Versus;
        text->SetText("Versus");
        break;

    case 2:
        m_CurrentScreen = dae::ScreenManager::GameMode::SinglePlayer;
        text->SetText("Single");
        break;
    }

    m_pScreenManager->SetCurrentEnum(m_CurrentScreen);

    SetKeyPressed(true);
}

void GameCommands::AcceptGameMode::Execute(float)
{
    if (GetKeyPressed()) return;

    if (dae::SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
    {
        dae::SceneManager::GetInstance().NextScene();
        dae::ScreenManager::GetInstance().CreateGameScreen(*dae::SceneManager::GetInstance().GetActiveScene());
        dae::servicelocator::get_sound_system().playMusic(0, 10);
        SetKeyPressed(true);
    }

    
}

void GameCommands::SkipLevel::Execute(float)
{
    if (GetKeyPressed()) return;

    if(dae::SceneManager::GetInstance().GetActiveSceneName() == "GameOver" ||
        dae::SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
    {
        SetKeyPressed(true);
        return;
    }

    dae::ScreenManager::GetInstance().ProceedNextLevel();

    SetKeyPressed(true);
}


void GameCommands::ResetLevel::Execute(float)
{
    if (GetKeyPressed()) return;

    if (dae::SceneManager::GetInstance().GetActiveSceneName() == "GameOver" ||
        dae::SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
    {
        SetKeyPressed(true);
        return;
    }
    
    dae::GameCollisionMngr::GetInstance().ClearAll();
    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
    dae::ScreenManager::GetInstance().CreateGameScreen(*dae::SceneManager::GetInstance().GetActiveScene());
}

void GameCommands::MuteMusic::Execute(float)
{
    if (GetKeyPressed()) return;

    dae::servicelocator::get_sound_system().MuteUnmute();

    SetKeyPressed(true);
}