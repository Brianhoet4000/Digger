#pragma once
#include <memory>
#include "BaseComponent.h"
#include "GameObserver.h"
#include "Subject.h"

namespace dae
{
	class SubjectComponent : public dae::BaseComponent
	{
	public:

		SubjectComponent(dae::GameObject* owner, std::shared_ptr<GameObserver> observer);

		virtual ~SubjectComponent() override = default;
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;

		std::shared_ptr<Subject> GetSubject() { return m_pSubject; }

	private:
		std::shared_ptr<Subject> m_pSubject;
	};

}
