#include <SDL.h>
#include "InputManager.h"
#include <map>
#include "ServiceLocator.h"

namespace dae
{
    class Transform;
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            return false;
        }
        if (e.type == SDL_KEYDOWN)
        {
            // Handle keydown events
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            // Handle mouse button events
        }
        // etc...
    }

    ProcessKeyboardInput(deltaTime);
    ProcessControllerInput(deltaTime);

    return true;
}

//Controller
void dae::InputManager::AddController(unsigned int id)
{
    m_Controllers.emplace_back(std::make_unique<Controller>(id));
}

void dae::InputManager::BindControllerToCommand(unsigned int id, Controller::ControllerButton& button, std::shared_ptr<Command> command, bool overwrite)
{
    ControllerKey key = ControllerKey(id, button);

    auto it = m_Commands.find(key);
    if (it != m_Commands.end())
    {
        if (overwrite)
        {
            it->second = command;  // Overwrite the existing command
        }
    }
    else
    {
        m_Commands.insert({ key, command });  // Add the new command if not found
    }
}

void dae::InputManager::UnBindControllerCommand(const std::shared_ptr<Command>& command)
{
    for (auto it = m_Commands.begin(); it != m_Commands.end(); ++it)
    {
        if (it->second == command)
        {
            m_Commands.erase(it);
            break;
        }
    }
}

void dae::InputManager::UnBindAllControllerCommands()
{
    m_Commands.clear();
    m_Controllers.clear();
}

void dae::InputManager::UpdateControllers() const
{
    for (const auto& controller : m_Controllers)
    {
        controller->Update();
    }
}

void dae::InputManager::ProcessControllerInput(float deltaTime) const
{
    for (const auto& controller : m_Controllers)
    {
        for (const auto& command : m_Commands)
        {
            const auto controllerKey = command.first.second;
            const unsigned int controllerId = command.first.first;
            if (controller->GetIDOfController() == controllerId && controller->IsPressed(static_cast<int>(controllerKey)))
            {
                command.second->Execute(deltaTime);
            }
            else
            {
                command.second->SetKeyPressed(false);
            }
        }
    }
}

//Keyboard
void dae::InputManager::BindKeyToCommand(const Uint8& key, std::shared_ptr<Command> command)
{
    m_KeyCommands.insert({ key, std::shared_ptr<Command>(command) });
}

void dae::InputManager::UnBindKey(const std::shared_ptr<Command>& command)
{
    for (auto it = m_KeyCommands.begin(); it != m_KeyCommands.end(); ++it)
    {
        if (it->second == command)
        {
            m_KeyCommands.erase(it);
            break;
        }
    }
}

void dae::InputManager::UnBindAllKeys()
{
    m_KeyCommands.clear();
}

void dae::InputManager::UnBindAllCommands()
{
    UnBindAllKeys();
    UnBindAllControllerCommands();
}

void dae::InputManager::ProcessKeyboardInput(float deltaTime) const
{
    const Uint8* pStates = SDL_GetKeyboardState(nullptr);

    for (auto& keyCommand : m_KeyCommands)
    {
        if (pStates[keyCommand.first])
        {
            keyCommand.second->Execute(deltaTime);
        }
        else
        {
            keyCommand.second->SetKeyPressed(false);
        }
    }
}