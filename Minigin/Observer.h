#pragma once
#include "Event.h"
#include <string>

namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void Notify(dae::Event event) = 0;
	};

}