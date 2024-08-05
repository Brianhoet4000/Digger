#pragma once
#include "BaseComponent.h"

namespace dae
{

	class PickUpComponent : public dae::BaseComponent
	{
	public:

		PickUpComponent(dae::GameObject* owner);

		virtual ~PickUpComponent() override = default;
		PickUpComponent(const PickUpComponent& other) = delete;
		PickUpComponent(PickUpComponent&& other) = delete;
		PickUpComponent& operator=(const PickUpComponent& other) = delete;
		PickUpComponent& operator=(PickUpComponent&& other) = delete;

		void Update(float) override;

	private:

	};

}