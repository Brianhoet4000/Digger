#pragma once
#include "BaseComponent.h"
#include "TextureTransformComponent.h"

namespace dae
{

	class ShootingDirComponent : public BaseComponent
	{
	public:

		ShootingDirComponent(GameObject* owner)
			:BaseComponent(owner)
		{
		}
		~ShootingDirComponent() = default;

		enum FaceState
		{
			Up,
			Right,
			Down,
			Left
		};

		FaceState returnFaceState() const { return m_FaceState; }

		void SetFaceState(FaceState state)
		{
			m_FaceState = state;
			const auto& transformComp = GetOwnerBaseComp()->GetComponent<dae::TextureTransformComponent>();

			switch (state)
			{
			case Up:
				transformComp->SetRotation(-90.0f);
				transformComp->SetFlip(false, false);
				break;

			case Down:
				transformComp->SetRotation(90.0f);
				transformComp->SetFlip(false, false);
				break;


			case Left:
				transformComp->SetRotation(0.0f);
				transformComp->SetFlip(true, false);
				break;
			case Right:
				transformComp->SetRotation(0.0f);
				transformComp->SetFlip(false, false);
				break;
			}
		}

	private:
		FaceState m_FaceState{ Right };
	};

}
