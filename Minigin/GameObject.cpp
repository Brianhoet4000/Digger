#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

#include "CollisionBoxComponent.h"
#include "CollisionBoxManager.h"

namespace dae
{
	GameObject::GameObject(const std::string& tag)
		:m_TagString{ tag }
	{
	}

	void GameObject::Update(float deltaTime) const
	{
		if (ReturnDeleting()) return;
		if (!m_Update) return;

		// Update all components
		for (const auto& pComponent : m_pComponents)
		{
			if (pComponent == nullptr)
			{
				continue;
			}

			pComponent->Update(deltaTime);
		}

		// Update all children
		for (const auto& pChild : m_pChildren)
		{
			if (pChild == nullptr)
				continue;

			pChild->Update(deltaTime);
		}
	}


	void GameObject::FixedUpdate(float deltaTime)
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->FixedUpdate(deltaTime);
		}

		for (const auto& child : m_pChildren)
		{
			child->FixedUpdate(deltaTime);
		}
	}

	void GameObject::Render() const
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->Render();
		}

		for (const auto& child : m_pChildren)
		{
			if (child->ReturnDeleting()) continue;

			child->Render();
		}
	}

	void GameObject::UpdateWorldPos()
	{
		if (m_DirtyFlag)
		{
			if (m_pParent == nullptr)
				m_WorldTransform = m_RelativeTransform;
			else
				m_WorldTransform = m_pParent->GetWorldPosition() + m_RelativeTransform;

			m_DirtyFlag = false;
		}
	}

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_pComponents.push_back(component);
	}

	void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
	}

	GameObject* GameObject::GetParent() const
	{
		return m_pParent;
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren() const
	{
		return m_pChildren;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (m_pParent)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = parent;

		if (!parent) return;

		UpdateWorldPos();
	}

	void GameObject::AddChild(const std::shared_ptr<GameObject>& child)
	{
		m_pChildren.emplace_back(child);
		child->SetParent(this);
	}

	void GameObject::RemoveAllComponents()
	{
		if (!m_pComponents.empty())
			m_pComponents.clear();
	}

	void GameObject::RemoveChild(const GameObject* child)
	{
		m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(),
			[&](const std::shared_ptr<GameObject>& ptr) {
				return ptr.get() == child;
			}), m_pChildren.end());
	}

	void GameObject::RemoveAllChilderen()
	{
		for (const auto& child : m_pChildren)
		{
			child->RemoveAllComponents();
		}
		m_pChildren.clear();
	}

	const glm::vec2& GameObject::GetWorldPosition()
	{
		if (m_DirtyFlag)
			UpdateWorldPos();
		return m_WorldTransform;
	}

	glm::vec2 GameObject::GetRelativePosition() const
	{
		return m_RelativeTransform;
	}

	void GameObject::SetRelativePosition(glm::vec2 Pos)
	{
		m_RelativeTransform = Pos;

		if (m_pParent == nullptr)
		{
			m_WorldTransform = m_RelativeTransform;
		}

		FlagIsTrue();
	}

	void GameObject::SetRelativePosition(float Posx, float Posy)
	{
		m_RelativeTransform.x = Posx;
		m_RelativeTransform.y = Posy;

		if (m_pParent == nullptr)
		{
			m_WorldTransform = m_RelativeTransform;
		}

		FlagIsTrue();
	}

	void GameObject::FlagIsTrue()
	{
		m_DirtyFlag = true;
		for (const auto& child : m_pChildren)
		{
			child->FlagIsTrue();
		}
	}

	std::string GameObject::GetTag() const
	{
		return m_TagString;
	}

	void GameObject::SetTag(const std::string& tag)
	{
		m_TagString = tag;
	}

	void GameObject::MarkTrueForDeleting()
	{
		for (const auto& pchild : m_pChildren)
		{
			if (pchild->ReturnDeleting())
				return;

			pchild->MarkTrueForDeleting();
		}

		m_DeleteParentFromScene = true;
	}

	bool GameObject::ReturnDeleting() const
	{
		return m_DeleteParentFromScene;
	}

	void GameObject::SetScene(Scene* scene)
	{
		m_pScene = scene;
		for (const auto& c : m_pChildren)
		{
			c->SetScene(scene);
		}
	}

	Scene* GameObject::GetScene() const
	{
		return m_pScene;
	}

}
