#include "Bullet.h"
#include "BulletComponent.h"
#include "GameCollisionComponent.h"
#include "TextureComponent.h"

dae::Bullet::Bullet(glm::vec2 pos, glm::vec2 vel)
	:m_Vel{ vel }
{
	m_pBullet = std::make_shared<dae::GameObject>("Bullet");

	//Texture
	const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pBullet.get());
	pTexture->SetTexture("Sprites/Bullet.png");
	m_pBullet->AddComponent(pTexture);

	//Collision
	const auto& pCollider = std::make_shared<dae::GameCollisionComponent>(m_pBullet.get());
	pCollider->SetRenderCollisionBox(false);
	pCollider->SetCollisionRectOffset(6);
	m_pBullet->AddComponent(pCollider);

	//BulletComponent
	const auto& pBulletComponent = std::make_shared<dae::BulletComponent>(m_pBullet.get(), m_Vel, 1);
	m_pBullet->AddComponent(pBulletComponent);

	//Pos
	m_pBullet->SetRelativePosition(pos);
}
