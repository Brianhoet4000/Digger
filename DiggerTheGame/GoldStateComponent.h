#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{

	class GoldStateComponent : public dae::BaseComponent
	{
	public:
		enum MoneyBagState
		{
			Full,
			Coins,
			Falling
		};

		GoldStateComponent(dae::GameObject* owner);

		virtual ~GoldStateComponent() override = default;
		GoldStateComponent(const GoldStateComponent& other) = delete;
		GoldStateComponent(GoldStateComponent&& other) = delete;
		GoldStateComponent& operator=(const GoldStateComponent& other) = delete;
		GoldStateComponent& operator=(GoldStateComponent&& other) = delete;

		void Update(float deltaTime) override;
		bool GetCoinsBool() const { return m_Broke; }

		MoneyBagState GetMoneyBagState() const { return m_MoneyState; }

	private:
		glm::vec2 m_Direction{ 0,5 };
		const float m_Speed{ 55.f };
		glm::vec2 m_EstimatedPos;

		bool m_ResetEstimatedPos = false;
		bool m_Broke = false;

		bool m_StartTimer = false;
		bool m_TimerDone = false;
		float m_Startvalue = 1.5f;
		float m_Countdownvalue = 0.f;

		MoneyBagState m_MoneyState{ Full };
	};

}
