#pragma once
#include "Event.h"
#include <vector>
#include <iostream>

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void NotifyObservers(Event event, GameObject* gameObject = nullptr) const;

	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;

	};
}