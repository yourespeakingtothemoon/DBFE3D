#include "Engine.h"
#include <iostream>

//pos, color, UV
float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Started...");

	dbf::initializeMemory();
	dbf::SetFilePath("../Assets");

	dbf::Engine::instance().init();
	dbf::Engine::instance().reg();
	LOG("Engine Initialized...");

	//create window
	dbf::g_renderer.generateWindow("DBF3", 800, 600, false);
	LOG("Window Generated...");

	//create framebuffer texture
	auto texture = std::make_shared<dbf::Texture>();
	texture->CreateTexture(1024, 1024); //512
	dbf::g_resourceManager.Add<dbf::Texture>("fb_texture", texture);

	//create framebuffer
	auto framebuffer = dbf::g_resourceManager.Get<dbf::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->unbind();

	// render pass 1 (render to framebuffer) 
	dbf::g_renderer.setViewport(0, 0, framebuffer->getSize().x, framebuffer->getSize().y);
	framebuffer->bind();
	dbf::g_renderer.openFrame();

	// render pass 2 (render to screen) 
	dbf::g_renderer.restoreViewport();
	dbf::g_renderer.openFrame();

	// load scene 
	auto scene = dbf::g_resourceManager.Get<dbf::Scene>("Scenes/basic.scn");

	
	std::vector<dbf::Transform> rando;
	

	bool quit = false;

	while (!quit)
	{
		dbf::Engine::instance().update();
		if (dbf::g_inputSystem.queryKeyState(dbf::key_escape) == dbf::InpSystem::keyState::Pressed) quit = true;

	

		
		scene->update();
		/*auto program = dbf::g_resourceManager.Get<dbf::Program>("shaders/fx/DualShader.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("i", interpolation);
			program->SetUniform("ri", refractionIndex);
		}*/

		//wave effect
		/*auto program2 = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (program2)
		{
			program2->Use();
			program2->SetUniform("offset", neu::g_time.time);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]); //x,y,z sliders
		ImGui::DragFloat("Interpolation", &interpolation, 0.05f, 0, 1); //x,y,z sliders
		ImGui::DragFloat("Refraction Index", &refractionIndex, 0.05f, 1, 4.1f); //x,y,z sliders
		ImGui::End();

		

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}*/
 
		/*// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		//scene->Render(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}*/

		dbf::g_renderer.openFrame();
		scene->preRender(dbf::g_renderer);
		scene->render(dbf::g_renderer);
 // POST_PROCESS
		//dbf::g_gui.Draw();

		dbf::g_renderer.closeFrame();
		//neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	dbf::Engine::instance().shutdown();

	return 0;
}