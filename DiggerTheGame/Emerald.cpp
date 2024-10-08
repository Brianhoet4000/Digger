#include "Emerald.h"
#include "GameCollisionComponent.h"
#include "GetOverlappedPlayer.h"
#include "PickUpComponent.h"
#include "TextureComponent.h"

dae::Emerald::Emerald(glm::vec2 pos)
{
	m_pEmerald = std::make_shared<dae::GameObject>("Emerald");

	//Texture
	const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pEmerald.get());
	m_pEmerald->AddComponent(pTexture);
	pTexture->SetTexture("Sprites/Emerald.png");

	//Collision
	const auto& pCollider = std::make_shared<dae::GameCollisionComponent>(m_pEmerald.get());
	pCollider->SetRenderCollisionBox(false);
	m_pEmerald->AddComponent(pCollider);

	const auto& pOverlappedComponent = std::make_shared<GetOverlappedPlayer>(m_pEmerald.get());
	m_pEmerald->AddComponent(pOverlappedComponent);

	const auto& pPickUpComponent = std::make_shared<PickUpComponent>(m_pEmerald.get());
	m_pEmerald->AddComponent(pPickUpComponent);

	//Pos
	m_pEmerald->SetRelativePosition({ pos });
}