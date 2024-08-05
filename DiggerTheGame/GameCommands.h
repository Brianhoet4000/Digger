#pragma once
#include "BulletTimerComponent.h"
#include "Commands.h"
#include "GameCollisionComponent.h"
#include "LevelPrefab.h"
#include "ScreenManager.h"

namespace GameCommands
{

	class DiggerMovement : public dae::Command
	{
	private:
		glm::vec2 m_Dir{};
		dae::GameCollisionComponent* m_pCollision;
		bool m_Digger;
		bool m_DoOnce = false;
	public:
		DiggerMovement(std::shared_ptr<dae::GameObject> owner, const glm::vec2& dir, bool digger);
		virtual void Execute(float deltaTime) override;
	};

	class ShootingBullet : public dae::Command
	{
	private:
		glm::vec2 m_Dir{};
		dae::Scene* m_Scene;
		dae::BulletTimerComponent* m_pBulletTimer{};
	public:
		ShootingBullet(std::shared_ptr<dae::GameObject> owner,dae::Scene* scene);
		virtual void Execute(float deltaTime) override;
	};

	class SwitchGameMode : public dae::Command
	{
	private:
		std::shared_ptr<dae::GameObject> m_pScreen{};
		dae::GameObject* m_pTextMode;
		dae::ScreenManager* m_pScreenManager{};
		dae::ScreenManager::GameMode& m_CurrentScreen;
	public:
		SwitchGameMode(std::shared_ptr<dae::GameObject> owner, dae::GameObject* text, dae::ScreenManager::GameMode& currentScreen, dae::ScreenManager* screen);
		virtual void Execute(float) override;

	};

	class AcceptGameMode : public dae::Command
	{
	private:
	public:
		AcceptGameMode() = default;
		virtual void Execute(float) override;
	};

	class SkipLevel : public dae::Command
	{
	private:
		bool m_CreatedEndScreen = false;
	public:
		SkipLevel() = default;
		virtual void Execute(float) override;
	};

	class ResetLevel : public dae::Command
	{
	private:

	public:
		ResetLevel() = default;
		virtual void Execute(float) override;
	};

	class MuteMusic : public dae::Command
	{
	private:

	public:
		MuteMusic() = default;
		virtual void Execute(float) override;
	};

}
