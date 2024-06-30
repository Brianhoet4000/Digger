#pragma once
#include <SDL_rect.h>

#include "BaseComponent.h"

namespace dae
{

	class GameCollisionComponent : public BaseComponent
	{
	public:

		GameCollisionComponent(GameObject* owner, bool IsVersus = false);
		virtual ~GameCollisionComponent() = default;
		GameCollisionComponent(const GameCollisionComponent& other) = delete;
		GameCollisionComponent(GameCollisionComponent&& other) = delete;
		GameCollisionComponent& operator=(const GameCollisionComponent& other) = delete;
		GameCollisionComponent& operator=(GameCollisionComponent&& other) = delete;

		virtual void Update(float) override;
		virtual void Render() const override;
		SDL_FRect GetCollisionRect() const;
		void SetCollisionRectOffset(float Offset);

		GameObject* GetOwner() const;

		bool GetRenderCollisionBox() const { return m_RenderCollisionBox; }
		void SetRenderCollisionBox(bool RenderCollisionBox) { m_RenderCollisionBox = RenderCollisionBox; }

		bool GetIsVersus() const { return m_IsVersus; }

	private:
		SDL_FRect m_CollisionBox;
		bool m_RenderCollisionBox = false;
		float m_Offset = 0;
		bool m_IsVersus;
	};

}
