#include "BulletTimerComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::BulletTimerComponent::BulletTimerComponent(dae::GameObject* owner)
	:BaseComponent(owner)
	,m_StartValue{5.f}
	,m_CurrentTime{m_StartValue}

{
}

void dae::BulletTimerComponent::Update(float deltaTime)
{
	if(m_HasShot)
	{
		const auto& pTex = GetOwnerBaseComp()->GetComponent<dae::TextureComponent>();

		m_CurrentTime -= 1 * deltaTime;

		if(GetOwnerBaseComp()->GetTag() == "Player_01")
		{
			pTex->SetTexture("Sprites/Player_Reloading.png");
		}
		if (GetOwnerBaseComp()->GetTag() == "Player_02")
		{
			pTex->SetTexture("Sprites/Player1_Reloading.png");
		}

		if(m_CurrentTime <= 0)
		{
			m_HasShot = false;
			m_CurrentTime = m_StartValue;

			if (GetOwnerBaseComp()->GetTag() == "Player_01")
			{
				pTex->SetTexture("Sprites/Player.png");
			}
			if (GetOwnerBaseComp()->GetTag() == "Player_02")
			{
				pTex->SetTexture("Sprites/Player1.png");
			}
		}
	}
}
