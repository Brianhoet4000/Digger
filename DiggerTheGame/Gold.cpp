#include "Gold.h"
#include "GameCollisionComponent.h"
#include "GetOverlappedPlayer.h"
#include "GoldStateComponent.h"
#include "PickUpComponent.h"
#include "TextureComponent.h"

dae::Gold::Gold(glm::vec2 pos)
{
	m_pGold = std::make_shared<dae::GameObject>("Gold");

	//Texture
	const auto& pTexture = std::make_shared<TextureComponent>(m_pGold.get());
	m_pGold->AddComponent(pTexture);
	pTexture->SetTexture("Sprites/GoldBag.png");

	//Collision
	const auto& pCollider = std::make_shared<GameCollisionComponent>(m_pGold.get());
	pCollider->SetRenderCollisionBox(false);
	m_pGold->AddComponent(pCollider);

	const auto& pOverlappedComponent = std::make_shared<GetOverlappedPlayer>(m_pGold.get());
	m_pGold->AddComponent(pOverlappedComponent);

	const auto& pPickUpComponent = std::make_shared<PickUpComponent>(m_pGold.get());
	m_pGold->AddComponent(pPickUpComponent);

	//GoldLogic
	const auto& pGoldStateCp = std::make_shared<GoldStateComponent>(m_pGold.get());
	m_pGold->AddComponent(pGoldStateCp);

	//Pos
	m_pGold->SetRelativePosition({ pos });
}
