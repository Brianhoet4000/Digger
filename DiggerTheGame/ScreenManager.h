#pragma once
#include "GameCollisionComponent.h"
#include "PlayerOne.h"
#include "Scene.h"
#include "TextComponent.h"

namespace dae
{

	class ScreenManager final : public Singleton<ScreenManager>
	{
	public:
		enum GameMode
		{
			SinglePlayer,
			Coop,
			Versus
		};
		
		virtual ~ScreenManager() = default;
		ScreenManager(const ScreenManager& other) = delete;
		ScreenManager(ScreenManager&& other) = delete;
		ScreenManager& operator=(const ScreenManager& other) = delete;
		ScreenManager& operator=(ScreenManager&& other) = delete;

		void CreateMenuScreen(dae::Scene& scene);
		void CreateGameScreen(dae::Scene& scene);

		void CreateGameOverScreen(dae::Scene& scene);

		int GetCurrentEnum() const { return m_CurrentGameMode; }
		void SetCurrentEnum(GameMode state)
		{
			m_CurrentGameMode = state;
		}

		int GetCurrentLevel() const { return m_CurrentLevel; }
		void ResetCurrentLevel() { m_CurrentLevel = 0; }
		void IncrementCurrentLevel() { ++m_CurrentLevel; }
		void WhenGameOver();
		void ResetAddedPlayers()
		{
			m_AddedPlayers = false;
		}

		void LevelCreator(dae::Scene& scene);
		void CreateUI(dae::Scene& scene, std::vector<std::shared_ptr<GameObject>>& players);
		GameObject* GetGameObjectInScene(dae::Scene& scene, std::string tag);
		std::shared_ptr<LevelPrefab> GetLevel() { return m_LevelPrefab; }

		void SkipToGameOverLevel();
		void ProceedNextLevel();

	private:
		friend class Singleton<ScreenManager>;
		ScreenManager() = default;
		GameMode m_CurrentGameMode{ SinglePlayer };
		const float m_Width{ 640 };
		const float m_Height{ 480 };

		std::shared_ptr<TextComponent> m_pGameModeDisplayText;
		std::shared_ptr<GameObject> m_pGameModeDisplay;
		int m_CurrentLevel{ 0 };
		bool m_AddedPlayers = false;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<LevelPrefab> m_LevelPrefab;
	};

}
