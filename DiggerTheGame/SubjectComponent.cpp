#include "SubjectComponent.h"

dae::SubjectComponent::SubjectComponent(dae::GameObject* owner, std::shared_ptr<GameObserver> observer)
	:BaseComponent(owner)
{
	m_pSubject = std::make_shared<Subject>();
	m_pSubject->AddObserver(observer);
}
