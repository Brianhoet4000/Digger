#include "PlayerOne.h"
#include <SDL_scancode.h>
#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>
#include "Counter.h"
#include "GameCommands.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"

dae::PlayerOne::PlayerOne(dae::Scene& scene)
{
	m_pPlayerOne = std::make_shared<dae::GameObject>("Player_01");

	//Texture
	const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pPlayerOne.get());
	pTexture->SetTexture("Sprites/Player.png");
	m_pPlayerOne->AddComponent(pTexture);

	//Collision
	const auto& pCollider = std::make_shared<dae::GameCollisionComponent>(m_pPlayerOne.get());
	m_pPlayerOne->AddComponent(pCollider);
	pCollider->SetCollisionRectOffset(5.f);
	pCollider->SetRenderCollisionBox(false);

	//BulletTimer
	const auto& pTimer = std::make_shared<dae::BulletTimerComponent>(m_pPlayerOne.get());
	m_pPlayerOne->AddComponent(pTimer);

	//ShootingDir
	const auto& pShootingDir = std::make_shared<ShootingDirComponent>(m_pPlayerOne.get());
	m_pPlayerOne->AddComponent(pShootingDir);

	//Movement
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerOne, m_Up, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerOne, m_Down, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerOne, m_Left, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerOne, m_Right, true);
	std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(m_pPlayerOne,&scene);

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_SPACE, ShootCommand);

	if (dae::ScreenManager::GetInstance().GetCurrentEnum() != dae::ScreenManager::SinglePlayer)
		m_Controller1Index = 1;
	else m_Controller1Index = 0;
	
	dae::InputManager::GetInstance().AddController(m_Controller1Index);

	dae::Controller::ControllerButton controllerButton{};

	controllerButton = dae::Controller::ControllerButton::DpadUp;
	dae::InputManager::GetInstance().BindControllerToCommand(m_Controller1Index, controllerButton, moveCommandUp);
	controllerButton = dae::Controller::ControllerButton::DpadDown;
	dae::InputManager::GetInstance().BindControllerToCommand(m_Controller1Index, controllerButton, moveCommandDown);
	controllerButton = dae::Controller::ControllerButton::DpadLeft;
	dae::InputManager::GetInstance().BindControllerToCommand(m_Controller1Index, controllerButton, moveCommandLeft);
	controllerButton = dae::Controller::ControllerButton::DpadRight;
	dae::InputManager::GetInstance().BindControllerToCommand(m_Controller1Index, controllerButton, moveCommandRight);
	controllerButton = dae::Controller::ControllerButton::ButtonA;
	dae::InputManager::GetInstance().BindControllerToCommand(m_Controller1Index, controllerButton, ShootCommand);
	

	const auto& pHealth = std::make_shared<dae::HealthComponent>(m_pPlayerOne.get(), 3);
	m_pPlayerOne->AddComponent(pHealth);

	const auto& pPoints = std::make_shared<dae::PointComponent>(m_pPlayerOne.get(), 0);
	m_pPlayerOne->AddComponent(pPoints);

	scene.Add(m_pPlayerOne);
}
