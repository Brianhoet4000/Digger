#include "LevelPrefab.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <random>
#include "Emerald.h"
#include "GameCollisionComponent.h"
#include "ConditionSingleCoopComponent.h"
#include "Gold.h"

dae::LevelPrefab::LevelPrefab(dae::Scene& scene, const std::string& LevelPath)
{
	m_pLevelObj = std::make_shared<dae::GameObject>();
	scene.Add(m_pLevelObj);

	constexpr int width{ 640 };
	constexpr int height{ 480 };
	std::vector<int> mapVector = dae::ResourceManager::GetInstance().ParseMapTxt("../Data/" + LevelPath);
	auto grid = ResourceManager::GetInstance().ReturnGrid();

	glm::vec2 startPos{ (width / 2) - ((float(grid.first) / 2.f) * 24), (height / 2) - ((float(grid.second)/ 2.f) * 24) };
	glm::vec2 pos{ startPos.x, startPos.y };
 
	for (size_t i = 0; i < mapVector.size(); ++i)
	{
		auto pBlock = std::make_shared<dae::GameObject>();

		auto pTexture = std::make_shared<dae::TextureComponent>(pBlock.get());

		m_pLevelObj->AddChild(pBlock);

		pBlock->AddComponent(pTexture);
		pBlock->SetRelativePosition({ pos.x, pos.y });

		pTexture->SetTexture("Path.png");
		pBlock->SetTag("Wall");
		auto Collider = std::make_shared<GameCollisionComponent>(pBlock.get());

		scene.Add(pBlock);
		m_pBlocks.push_back(pBlock);

		const glm::vec2 size{ pTexture->GetSize() };

		switch (mapVector[i])
		{
		case 0:
			pTexture->SetTexture("UnbreakableWall.png");
			pBlock->SetTag("Wall");
			pBlock->AddComponent(Collider);
			break;
		case 1:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			break;
		case 2:
			pTexture->SetTexture("Spawn.png");
			pBlock->SetTag("Spawn");
			m_SpawnPositions.push_back(pos);
			break;
		case 3:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			m_BlockPositions.push_back(pos);
			break;
		case 4:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			m_BlockPositions.push_back(pos);
			m_EmeraldPositions.push_back(pos);
			break;
		case 5:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			m_BlockPositions.push_back(pos);
			m_GoldPositions.push_back(pos);
			break;
		case 6:
			m_EnemySpawnPositions = pos;
			break;
			default:
				break;
		}
		pos.x += size.x;


		if ((i + 1) % grid.first == 0)
		{
			pos.x = startPos.x;
			pos.y += size.y;
		}
	}

	AddBreakAbleBlocks(scene);
	AddEmeralds(scene);
	AddGold(scene);

	
}

void dae::LevelPrefab::AddBreakAbleBlocks(dae::Scene& scene)
{
	for (size_t i = 0; i < m_BlockPositions.size(); ++i)
	{
		auto pBreakBlock = std::make_shared<dae::GameObject>();
		pBreakBlock->SetTag("Break");
	
		//Texture
		auto pBreakTexture = std::make_shared<dae::TextureComponent>(pBreakBlock.get());
		pBreakBlock->AddComponent(pBreakTexture);
		pBreakTexture->SetTexture("BreakableWall.png");
	
		//Collision
		auto pBreakCollider = std::make_shared<dae::GameCollisionComponent>(pBreakBlock.get());
		pBreakBlock->AddComponent(pBreakCollider);
	
		//Pos
		pBreakBlock->SetRelativePosition({ m_BlockPositions[i].x, m_BlockPositions[i].y }); // Position it above the path block

		scene.Add(pBreakBlock);
	}
}

void dae::LevelPrefab::AddEmeralds(dae::Scene& scene)
{
	for (size_t i = 0; i < m_EmeraldPositions.size(); ++i)
	{
		auto newEmerald = std::make_shared<dae::Emerald>(m_EmeraldPositions[i]);
		scene.Add(newEmerald->ReturnEmerald());
	}
}

void dae::LevelPrefab::AddGold(dae::Scene& scene)
{
	for (size_t i = 0; i < m_GoldPositions.size(); ++i)
	{
		m_GoldPositions[i].y = m_GoldPositions[i].y + 2.0f;
		auto newGold = std::make_shared<dae::Gold>(m_GoldPositions[i]);
		scene.Add(newGold->ReturnGold());
	}
}
