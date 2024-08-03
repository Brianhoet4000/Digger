#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
    m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
    m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void dae::Subject::NotifyObservers(dae::Event event, GameObject* gameObject) const
{
    for (auto& observer : m_pObservers)
    {
        observer->Notify(event, gameObject);
    }
}
