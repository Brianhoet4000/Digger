#pragma once
#include "Scene.h"

namespace dae
{

	unsigned int Scene::m_IdCounter = 0;

	Scene::Scene(const std::string& name) : m_Name(name) {}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameObject> object)
	{
		object->SetScene(this);
		m_pObjects.emplace_back(std::move(object));
	}

	void Scene::Remove(const std::shared_ptr<GameObject>& object)
	{
		//remove children
		for (const auto& c : object->GetChildren())
		{
			m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), c), m_pObjects.end());
		}

		//remove object
		m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
	}

	void Scene::Remove(const GameObject* object)
	{
		m_pObjects.erase(
			std::remove_if(
				m_pObjects.begin(),
				m_pObjects.end(),
				[&object](const std::shared_ptr<GameObject>& ptr) { return ptr.get() == object; }
			),
			m_pObjects.end()
		);

	}

	void Scene::RemoveAll()
	{
		m_pObjects.clear();
	}

	void Scene::Update(float deltaTime)
	{
		for (auto& object : m_pObjects)
		{
			if (object.get() == nullptr) return;

			if (object->ReturnDeleting())
			{
				Remove(object);
				continue;
			}

			object->Update(deltaTime);
		}
	}

	void Scene::FixedUpdate(float deltaTime) const
	{
		for (auto& object : m_pObjects)
		{
			if (!object) return;

			if (object->ReturnDeleting())
			{
				continue;
			}

			object->FixedUpdate(deltaTime);
		}
	}

	void Scene::UpdateCleanUp()
	{
		m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [](const std::shared_ptr<GameObject>& pGameObject)
			{
				return pGameObject->ReturnDeleting();
			}), m_pObjects.end());
	}

	void Scene::Render() const
	{
		for (const auto& object : m_pObjects)
		{
			if (!object) return;

			if (object->ReturnDeleting())
			{
				continue;
			}

			object->Render();
		}
	}

}