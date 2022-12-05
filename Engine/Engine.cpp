#include "Engine.h"

namespace dbf
{
	InpSystem g_inputSystem;
	Renderer g_renderer;
	TimeMgmt g_time;
	//GUI g_gui;

	AudioSystem g_audioSystem;
	ResourceMgmt g_resourceManager;
	PhysicsSystem g_physicsSystem;
	EventMgmt g_eventManager;


	void Engine::reg()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(PlayComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(LightComponent);
	}
	void Engine::init()
	{
		g_renderer.init();
		g_inputSystem.init();
		g_audioSystem.init();
		g_resourceManager.init();
		g_physicsSystem.init();
		g_eventManager.init();
	}

	void Engine::update()
	{
		//SDL_Event event;
		//while (SDL_PollEvent(&event)) {g_gui.update(event);}
		g_time.gameTick();
		g_eventManager.update();
		g_physicsSystem.update();
		g_inputSystem.update();
		g_audioSystem.update();
	}

	void Engine::shutdown()
	{
		Factory::instance().shutdown();

		g_eventManager.shutdown();
		g_physicsSystem.shutdown();
		g_resourceManager.shutdown();
		//g_gui.shutdown();
		g_inputSystem.shutdown();
		g_audioSystem.shutdown();
		g_renderer.shutdown();
		
	}

}