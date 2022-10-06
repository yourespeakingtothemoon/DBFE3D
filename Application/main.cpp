#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
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
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();
		dbf::g_renderer.closeFrame();
	}

	dbf::Engine::instance().shutdown();
	return 0;
}