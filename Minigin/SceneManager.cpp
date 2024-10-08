#include "SceneManager.h"
#include "Scene.h"

using namespace dae;

void SceneManager::Update(float deltaTime) const
{
	for (const auto& scene : m_pScenes)
	{
		if (scene == nullptr)
			continue;

		if (!scene->IsActive())
			continue;

		scene->Update(deltaTime);
		return;
	}
}

void SceneManager::FixedUpdate(float fixedTimeStep) const
{
	for (const auto& scene : m_pScenes)
	{
		if (!scene->IsActive())
			continue;

		scene->FixedUpdate(fixedTimeStep);
		return;
	}
}

void dae::SceneManager::UpdateCleanUp() const
{
	for (const auto& scene : m_pScenes)
	{
		if (!scene->IsActive())
			continue;

		scene->UpdateCleanUp();
		return;
	}
}

void SceneManager::Render() const
{
	for (const auto& scene : m_pScenes)
	{
		if (!scene->IsActive())
			continue;

		scene->Render();
		return;
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	return *scene;
}

void SceneManager::NextScene()
{
	m_pScenes[m_ActiveScene]->SetActive(false);

	++m_ActiveScene;
	if (m_ActiveScene >= static_cast<int>(m_pScenes.size()))
		m_ActiveScene = 0;

	m_pScenes[m_ActiveScene]->SetActive(true);
}

void SceneManager::SetActiveScene(const std::string& sceneName)
{
	m_pScenes[m_ActiveScene]->SetActive(false);

	for (int i{}; i < static_cast<int>(m_pScenes.size()); ++i)
	{
		if (m_pScenes[i]->GetName() != sceneName) continue;

		m_ActiveScene = i;
		m_pScenes[m_ActiveScene]->SetActive(true);
	}
}

std::string SceneManager::GetActiveSceneName() const
{
	return m_pScenes[m_ActiveScene]->GetName();
}

void dae::SceneManager::DeleteAllObjects()
{
	for (const auto& scene : m_pScenes)
	{
		scene->MarkAllTrue();
	}
}
