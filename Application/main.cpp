#include "Engine.h" 
#include <iostream> 

int main()
{
	dbf::initializeMemory();

	dbf::Engine::instance().init();
	dbf::Engine::instance().reg();

	dbf::g_renderer.generateWindow("dbfe 3d engine", 800, 600);

	bool quit = false;
	while (!quit)
	{
		dbf::Engine::instance().update();

		if (dbf::g_inputSystem.queryKeyState(dbf::key_escape) == dbf::InpSystem::keyState::Pressed) quit = true;

		dbf::g_renderer.openFrame();
		dbf::g_renderer.closeFrame();
	}

	dbf::Engine::instance().shutdown();
}