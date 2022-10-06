#include "ContactListener.h"
#include "Framework/Actor.h"
#include "Framework/Components/CollisionComponent.h"
#include <iostream>

namespace dbf
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);
			if (actorA->getComponent<CollisionComponent>())
			{
				actorA->getComponent<CollisionComponent>()->enterCollide(actorB);
			}
			if (actorB->getComponent<CollisionComponent>())
			{
				actorB->getComponent<CollisionComponent>()->enterCollide(actorA);
			}
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);
			if (actorA->queryDestroy() || actorB->queryDestroy())return;
			if (actorA->getComponent<CollisionComponent>())
			{
				actorA->getComponent<CollisionComponent>()->exitCollide(actorB);
			}
			if (actorB->getComponent<CollisionComponent>())
			{
				actorB->getComponent<CollisionComponent>()->exitCollide(actorA);
			}
		}
	}
}
