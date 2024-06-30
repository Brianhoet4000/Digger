#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "Scene.h"

namespace dae
{
	class LevelPrefab final
	{
	public:
		LevelPrefab(dae::Scene& scene,const std::string& LevelPath);

		~LevelPrefab() = default;
		LevelPrefab(const LevelPrefab& other) = delete;
		LevelPrefab(LevelPrefab&& other) = delete;
		LevelPrefab& operator=(const LevelPrefab& other) = delete;
		LevelPrefab& operator=(LevelPrefab&& other) = delete;

		std::vector<glm::vec2> GetSpawnPosition() const { return m_SpawnPositions; }
		glm::vec2 GetEnemySpawnPosition() const { return m_EnemySpawnPositions; }
		void AddBreakAbleBlocks(dae::Scene& scene);
		void AddEmeralds(dae::Scene& scene);
		void AddGold(dae::Scene& scene);

		std::shared_ptr<GameObject> returnLevelObj() { return m_pLevelObj; }
		std::vector<std::shared_ptr<dae::GameObject>> returnBlocks() { return m_pBlocks; }

	private:
		std::vector<glm::vec2> m_SpawnPositions{};
		glm::vec2 m_EnemySpawnPositions{};
		std::vector<glm::vec2> m_BlockPositions{};
		std::vector<glm::vec2> m_EmeraldPositions{};
		std::vector<glm::vec2> m_GoldPositions{};

		std::shared_ptr<GameObject> m_pLevelObj;
		std::vector <std::shared_ptr<dae::GameObject>> m_pBlocks;
	};

}