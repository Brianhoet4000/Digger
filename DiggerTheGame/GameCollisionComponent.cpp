#include "GameCollisionComponent.h"

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::GameCollisionComponent::GameCollisionComponent(dae::GameObject* owner, bool IsVersus)
	:BaseComponent(owner)
	,m_IsVersus{ IsVersus }
{
	m_CollisionBox.w = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>()->GetSize().x;
	m_CollisionBox.h = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>()->GetSize().y;

	GameCollisionMngr::GetInstance().AddCollisionBox(GetOwnerBaseComp(), this);
}

void dae::GameCollisionComponent::Update(float)
{
	m_CollisionBox.x = GetOwnerBaseComp()->GetWorldPosition().x + m_Offset;
	m_CollisionBox.y = GetOwnerBaseComp()->GetWorldPosition().y + m_Offset;
}

void dae::GameCollisionComponent::Render() const
{
	if (m_RenderCollisionBox)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 0, 1);
		SDL_RenderDrawRectF(Renderer::GetInstance().GetSDLRenderer(), &m_CollisionBox);
	}
}

SDL_FRect dae::GameCollisionComponent::GetCollisionRect() const
{
	return m_CollisionBox;
}

void dae::GameCollisionComponent::SetCollisionRectOffset(float Offset)
{
	m_Offset = Offset;
	m_CollisionBox.w = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>()->GetSize().x - (Offset * 2.0f);
	m_CollisionBox.h = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>()->GetSize().y - (Offset * 2.0f);
}
