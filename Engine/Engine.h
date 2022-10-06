#pragma once

#include "Serialization/Json.h" 

#include "Core/MemoryMgmt.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"

#include "Framework/EventSystem/EventMgmt.h"

#include "Framework/Components/PlayComponent.h"
#include "Framework/Components/AudioComponent.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/RBPhysicsComponent.h"
#include "Framework/Components/ModelComponent.h"
#include "Framework/Components/SpriteAnimComponent.h"
#include "Framework/Components/TextComponent.h"
#include "Framework/Components/TilemapComponent.h"
#include "Framework/Components/CharComponent.h"
#include "Framework/Components/CameraComponent.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Resource/ResourceMgmt.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"


#include <memory>
#include<variant>
#include<vector>
#include<list>


namespace dbf 
{
	extern InpSystem g_inputSystem;
	extern Renderer g_renderer;
	extern TimeMgmt g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceMgmt g_resourceManager;
	extern PhysicsSystem g_physicsSystem;
	extern EventMgmt g_eventManager;

	class Engine : public Singleton<Engine>
	{
	public:
		void reg();
		void init();
		void shutdown();
		void update();
	};
}