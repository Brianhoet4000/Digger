#include "LevelPrefab.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <random>
#include "Emerald.h"
#include "GameCollisionComponent.h"
#include "Gold.h"
#include "rapidjson.h"
#include <fstream>
#include <istreamwrapper.h>

#include "PickUpComponent.h"

dae::LevelPrefab::LevelPrefab(dae::Scene& scene, const std::string& LevelPath)
{
	m_pLevelObj = std::make_shared<dae::GameObject>();
	scene.Add(m_pLevelObj);

	constexpr int width{ 640 };
	constexpr int height{ 480 };

	//New
	std::string fileName = "../Data/Levels/" + LevelPath + ".json";
	std::ifstream inputFile(fileName);

	// Check if file was opened successfully
	if (!inputFile.is_open())
	{
		// Handle error opening file
		std::cout << "File didn't open\n";
		return;
	}

	// Read the entire file into a string
	std::string fileContents((std::istreambuf_iterator<char>(inputFile)),
		std::istreambuf_iterator<char>());

	// Close the input file
	inputFile.close();

	rapidjson::Document document;
	document.Parse(fileContents.c_str());


	// Read the grid dimensions
	if (document.HasMember("Grid") && document["Grid"].IsArray() && document["Grid"].Size() == 2)
	{
		const auto& gridArray = document["Grid"].GetArray();
		m_Grid.first = gridArray[0].GetInt();
		m_Grid.second = gridArray[1].GetInt();
	}

	glm::vec2 startPos{ (width / 2) - ((float(m_Grid.first) / 2.f) * 24), (height / 2) - ((float(m_Grid.second) / 2.f) * 24) };
	glm::vec2 pos{ startPos.x, startPos.y };


	const auto& levelArray = document["Level"].GetArray();

	for (rapidjson::SizeType i = 0; i < levelArray.Size(); ++i)
	{
		if (!levelArray[i].IsInt())
		{
			std::cout << "Invalid JSON entry\n";
			continue;
		}

		int num = levelArray[i].GetInt();

		auto pBlock = std::make_shared<dae::GameObject>();
		auto pTexture = std::make_shared<dae::TextureComponent>(pBlock.get());

		m_pLevelObj->AddChild(pBlock);

		pBlock->AddComponent(pTexture);
		pBlock->SetRelativePosition({ pos.x, pos.y });

		pTexture->SetTexture("Sprites/Path.png");
		pBlock->SetTag("Wall");
		const auto& Collider = std::make_shared<GameCollisionComponent>(pBlock.get());

		scene.Add(pBlock);
		m_pBlocks.push_back(pBlock);

		const glm::vec2 size{ pTexture->GetSize() };

		switch (num)
		{
		case 0:
			pTexture->SetTexture("Sprites/UnbreakableWall.png");
			pBlock->SetTag("Wall");
			pBlock->AddComponent(Collider);
			break;
		case 1:
			pTexture->SetTexture("Sprites/Path.png");
			pBlock->SetTag("Path");
			break;
		case 2:
			pTexture->SetTexture("Sprites/Spawn.png");
			pBlock->SetTag("Spawn");
			m_SpawnPositions.push_back(pos);
			break;
		case 3:
			pTexture->SetTexture("Sprites/Path.png");
			pBlock->SetTag("Path");
			m_BlockPositions.push_back(pos);
			break;
		case 4:
			pTexture->SetTexture("Sprites/Path.png");
			pBlock->SetTag("Path");
			m_BlockPositions.push_back(pos);
			m_EmeraldPositions.push_back(pos);
			break;
		case 5:
			pTexture->SetTexture("Sprites/Path.png");
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


		if ((i + 1) % m_Grid.first == 0)
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
		const auto& pBreakTexture = std::make_shared<dae::TextureComponent>(pBreakBlock.get());
		pBreakBlock->AddComponent(pBreakTexture);
		pBreakTexture->SetTexture("Sprites/BreakableWall.png");
	
		//Collision
		const auto& pBreakCollider = std::make_shared<dae::GameCollisionComponent>(pBreakBlock.get());
		pBreakBlock->AddComponent(pBreakCollider);

		const auto& pBreakPickUp = std::make_shared<dae::PickUpComponent>(pBreakBlock.get());
		pBreakBlock->AddComponent(pBreakPickUp);
	
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