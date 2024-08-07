#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "GoldState.h"

namespace dae
{
	class GoldStateComponent : public dae::BaseComponent
	{
	public:
		GoldStateComponent(dae::GameObject* owner);

		virtual ~GoldStateComponent() override = default;
		GoldStateComponent(const GoldStateComponent& other) = delete;
		GoldStateComponent(GoldStateComponent&& other) = delete;
		GoldStateComponent& operator=(const GoldStateComponent& other) = delete;
		GoldStateComponent& operator=(GoldStateComponent&& other) = delete;

		void Update(float deltaTime) override;
		bool GetCoinsBool() const { return m_Broke; }
		void SetCoinsBool(bool broken) { m_Broke = broken; }

		GoldState* GetCurrentState() const { return m_CurrentState; }
		GoldState* GetIdleState() const { return m_IdleState; }
		GoldState* GetHoverState() const { return m_HoverState; }
		GoldState* GetFallingState() const { return m_FallingState; }
		GoldState* GetCoinState() const { return m_CoinState; }

		void ChangeState(GoldState* newState);


	private:
		bool m_Broke = false;

		GoldState* m_IdleState;
		GoldState* m_HoverState;
		GoldState* m_FallingState;
		GoldState* m_CoinState;
		GoldState* m_CurrentState;
	};

}
