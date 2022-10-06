#include "PlayComponent.h"
#include "Engine.h"
#include <iostream>

namespace dbf
{
	void PlayComponent::init()
	{
		CharComponent::init();
	}

	void PlayComponent::update()
	{

		if (atkOutput > 0) {
			atkOutput--;
		}
		
		Vector2 direction = Vector2::zero;
		//input
			//check
		bool left = dbf::g_inputSystem.queryKeyState(dbf::key_a) == dbf::InpSystem::keyState::Held;
		bool right = dbf::g_inputSystem.queryKeyState(dbf::key_d) == dbf::InpSystem::keyState::Held;
		bool jump = m_jumpCount < 2 && dbf::g_inputSystem.queryKeyState(dbf::key_space) == dbf::InpSystem::keyState::Pressed;
		bool atk = dbf::g_inputSystem.queryKeyState(dbf::key_k) == dbf::InpSystem::keyState::Pressed;
	
		bool mage = dbf::g_inputSystem.queryKeyState(dbf::key_l) == dbf::InpSystem::keyState::Pressed;
			//act
		if (left)	direction = Vector2::left;
		if (right) direction = Vector2::right;
		if (jump)
		{
			auto component = m_owner->getComponent<PhysicsComponent>();
			if (component)
			{
				m_jumpCount+=1;
				component->applyForce(Vector2::up * 800);
			}

		}
		if (atk) { atkOutput += 10; }
		
			
			
		
		Vector2 velocity;

		//physics
		auto component = m_owner->getComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force 
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->applyForce(direction * speed);
			velocity = component->velocity;
		}
		//sequence set
		auto animComponent = m_owner->getComponent<SpriteAnimComponent>();
		
		if (animComponent)
		{
			if (atkOutput > 0)
			{
				animComponent->setSequence("attack");
				auto actor = dbf::Factory::instance().Create<dbf::Actor>("Hitbox");
				if (!animComponent->getFlipHoriz()) {
					actor->m_transform.position = { m_owner->m_transform.position + Vector2{64,0} };
				}if (animComponent->getFlipHoriz()) {
					actor->m_transform.position = { m_owner->m_transform.position - Vector2{64,0} };
				}
				actor->init();

				m_owner->getScene()->Add(std::move(actor));

			}
			else {

				if (velocity.x != 0) animComponent->setFlipHoriz(velocity.x < 0);


				//else { animComponent->setSequence("idle"); }

				if (velocity.y < 0)
				{
					animComponent->setSequence("jump");
				}
				if (velocity.y > 0)
				{
					animComponent->setSequence("fall");

				}


				if (m_groundCount > 0) {

					if (std::fabs(velocity.x) > 0)
					{
						animComponent->setSequence("run");
					}
					else
					{
						animComponent->setSequence("idle");
					}

				}



			}
		
		}

		


		// set camera 
		auto camera = m_owner->getScene()->getActorByName("Camera");
		if (camera)
		{
			camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}




		//update
		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;



	}
	void PlayComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.eventData);
			if (health <= 0)
			{
				//player die
			}
		}
	}
	bool PlayComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayComponent::read(const rapidjson::Value& value)
	{
		CharComponent::read(value);
		READ_DATA(value, jump);
		return true;
	}

	void PlayComponent::enterCollide(Actor* other)
	{

		if (other->getTag() == "pyMagick")
		{
			other->flipDestroy();
			pyMagicka++;

		}

	

		if (other->getTag() == "Enemy")
		{
			health -= 1;
			if (health <= 0)
			{
				m_owner->flipDestroy();
			}

			//dbf::g_eventManager.notify({ "EVENT_DAMAGE", other, damage });
		}
		if (other->getTag() == "Ground")
		{
			m_groundCount++;
			m_jumpCount=0;
		}
	}
	void PlayComponent::exitCollide(Actor* other)
	{
		if (other->getTag() == "Ground")
		{
			m_groundCount--;
			
		}
	}
	void PlayComponent::attack(bool form)
	{
		
		
	}
}
