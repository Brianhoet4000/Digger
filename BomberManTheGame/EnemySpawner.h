#pragma once
#include <glm/vec2.hpp>
#include "Scene.h"
#include "SpawnTimerComponent.h"
#include "GameObject.h"

namespace dae
{

	class EnemySpawner final
	{
	public:
		EnemySpawner(dae::Scene& scene,glm::vec2 StartPos, int MaxEnemies);

		~EnemySpawner() = default;
		EnemySpawner(const EnemySpawner& other) = delete;
		EnemySpawner(EnemySpawner&& other) = delete;
		EnemySpawner& operator=(const EnemySpawner& other) = delete;
		EnemySpawner& operator=(EnemySpawner&& other) = delete;

		std::shared_ptr<dae::GameObject> getSpawnObj() { return m_pSpawner; }

	private:
		std::shared_ptr<dae::GameObject> m_pSpawner;
	};

}
