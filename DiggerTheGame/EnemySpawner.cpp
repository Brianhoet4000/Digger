#include "EnemySpawner.h"
#include <memory>
#include "SpawnTimerComponent.h"
#include "EnemyPrefab.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::EnemySpawner::EnemySpawner(dae::Scene& scene, glm::vec2 StartPos, int MaxEnemies)
{
	m_pSpawner = std::make_shared<dae::GameObject>();
	m_pSpawner->SetRelativePosition(StartPos);

	const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pSpawner.get());
	pTexture->SetTexture("Sprites/Cherry.png");
	pTexture->SetMustRender(false);
	m_pSpawner->AddComponent(pTexture);

	//Timer
	const auto& pTimer = std::make_shared<dae::SpawnTimerComponent>(&scene, m_pSpawner.get(), 7.f, MaxEnemies);
	m_pSpawner->AddComponent(pTimer);

	scene.Add(m_pSpawner);
}
