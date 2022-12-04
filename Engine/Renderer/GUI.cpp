#include "GUI.h"

namespace dbf
{
	void GUI::init(Renderer& renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplSDL2_InitForOpenGL(renderer.m_window, renderer.m_context);
		const char* glsl_version = "#version 430";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::StyleColorsDark();
	}

	void GUI::shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::openFrame(Renderer& renderer)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		//ImGui_ImplSDL2_NewFrame(renderer.m_window);
		ImGui::NewFrame();
	}

	void GUI::closeFrame()
	{
		ImGui::EndFrame();
	}

	void GUI::draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::update(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
}