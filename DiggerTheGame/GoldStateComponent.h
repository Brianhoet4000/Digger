#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "BaseComponent.h"
#include "GoldState.h"

namespace dae
{
	class GoldStateComponent : public dae::BaseComponent
	{
	public:
		GoldStateComponent(dae::GameObject* owner);

		virtual ~GoldStateComponent() override;

		GoldStateComponent(const GoldStateComponent& other) = delete;
		GoldStateComponent(GoldStateComponent&& other) = delete;
		GoldStateComponent& operator=(const GoldStateComponent& other) = delete;
		GoldStateComponent& operator=(GoldStateComponent&& other) = delete;

		void Update(float deltaTime) override;

		bool GetCoinsBool() const { return m_Broke; }
		void SetCoinsBool(bool broken) { m_Broke = broken; }

		GoldState* GetCurrentState() const { return m_CurrentState; }
		GoldState* GetIdleState() const { return m_IdleState.get(); }
		GoldState* GetHoverState() const { return m_HoverState.get(); }
		GoldState* GetFallingState() const { return m_FallingState.get(); }
		GoldState* GetCoinState() const { return m_CoinState.get(); }

		void ChangeState(GoldState* newState);

	private:
		bool m_Broke = false;

		std::unique_ptr<GoldState> m_IdleState;
		std::unique_ptr<GoldState> m_HoverState;
		std::unique_ptr<GoldState> m_FallingState;
		std::unique_ptr<GoldState> m_CoinState;
		GoldState* m_CurrentState;
	};
}
