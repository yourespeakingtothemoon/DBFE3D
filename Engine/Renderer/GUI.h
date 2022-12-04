#pragma once
#include "Renderer.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>

namespace dbf
{
	class GUI
	{
	public:
		GUI() = default;
		~GUI() = default;

		void init(Renderer& renderer);
		void shutdown();

		void openFrame(Renderer& renderer);
		void closeFrame();
		void draw();

		void update(SDL_Event& event);
	};
}
