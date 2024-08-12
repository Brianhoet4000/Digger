#pragma once
#include "GameObject.h"
#include "SceneManager.h"


namespace dae
{
	class GameObject;
	class TextComponent;

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(const std::shared_ptr<GameObject>& object);
		void Remove(const GameObject* object);
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime) const;
		void UpdateCleanUp();
		void Render() const;

		std::string GetName() const { return m_Name; }
		std::vector<std::shared_ptr<GameObject>> GetGameObjects() { return m_pObjects; }

		void SetActive(bool isActive) { m_IsActive = isActive; }
		bool IsActive() const { return m_IsActive; }
		void MarkAllTrue() const
		{
			for (const auto& element : m_pObjects)
			{
				// Properly check if the tag is "Player_01" or "Player_02"
				if (element->GetTag() == "Player_01" || element->GetTag() == "Player_02")
					continue;

				element->MarkTrueForDeleting();
			}
		}

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};

		bool m_IsActive{};

		static unsigned int m_IdCounter;
	};

}
