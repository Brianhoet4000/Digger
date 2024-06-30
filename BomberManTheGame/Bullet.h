#pragma once
#include "GameObject.h"

namespace dae
{
	class Bullet final
	{
	public:
		Bullet(glm::vec2 pos, glm::vec2 vel);
		std::shared_ptr<dae::GameObject> ReturnBullet() { return m_pBullet; }

		~Bullet() = default;
		Bullet(const Bullet& other) = delete;
		Bullet(Bullet&& other) = delete;
		Bullet& operator=(const Bullet& other) = delete;
		Bullet& operator=(Bullet&& other) = delete;

	private:
		std::shared_ptr<dae::GameObject> m_pBullet;
		glm::vec2 m_Vel;
	};
}