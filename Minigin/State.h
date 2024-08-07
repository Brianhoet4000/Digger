#pragma once
#include "BaseComponent.h"

namespace dae
{
	class State
	{
	public:
		virtual ~State() = default;

		virtual void OnEnter(BaseComponent* component) = 0;
		virtual void Update(BaseComponent* component, float deltaTime) = 0;
		virtual void OnExit(BaseComponent* component) = 0;
	};
}
