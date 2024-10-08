#include <stdexcept>
#include "Renderer.h"

#include <chrono>
#include <iostream>

#include "SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

// Overload for rendering without rotation and flipping
void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
    SDL_Rect dst{};
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y);
    SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

// Overload for rendering with scaling but without rotation and flipping
void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
    SDL_Rect dst{};
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y);
    dst.w = static_cast<int>(width);
    dst.h = static_cast<int>(height);
    SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

// Overload for rendering with rotation and flipping (new method)
void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float rotation, const bool flipX, const bool flipY) const
{
    SDL_Rect dst{};
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y);
    SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

    SDL_Point center = { dst.w / 2, dst.h / 2 };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flipX) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    if (flipY) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

    SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotation, &center, flip);
}

// Overload for rendering with scaling, rotation, and flipping
void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float rotation, const bool flipX, const bool flipY) const
{
    SDL_Rect dst{};
    dst.x = static_cast<int>(x);
    dst.y = static_cast<int>(y);
    dst.w = static_cast<int>(width);
    dst.h = static_cast<int>(height);

    SDL_Point center = { dst.w / 2, dst.h / 2 };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flipX) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    if (flipY) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

    SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, rotation, &center, flip);
}



inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
