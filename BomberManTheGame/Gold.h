#pragma once
#include "GameObject.h"

namespace dae
{

	class Gold final
	{
	public:
		Gold(glm::vec2 pos);
		std::shared_ptr<dae::GameObject> ReturnGold() { return m_pGold; }

		~Gold() = default;
		Gold(const Gold& other) = delete;
		Gold(Gold&& other) = delete;
		Gold& operator=(const Gold& other) = delete;
		Gold& operator=(Gold&& other) = delete;


	private:
		std::shared_ptr<dae::GameObject> m_pGold;
	};

}