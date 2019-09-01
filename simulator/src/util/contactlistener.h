#pragma once

#include "Box2D/Box2D.h"
#include "../creature/creature.h"

enum ContactType {
	TERRAIN = 0x0001,
	CREATURE = 0x0002,
	PLANT = 0x0004,
	MOUTH = 0x0008
};

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {
		Creature* creatureA = nullptr;
		Creature* creatureB = nullptr;
		b2Fixture* other = nullptr;

		if (CreaturePresent(contact, creatureA, other)) {
			if (creatureA == nullptr || other == nullptr) return;

			ContactType type = (ContactType)other->GetFilterData().categoryBits;

			switch (type) {
			case ContactType::CREATURE:
				creatureB = (Creature*)other->GetUserData();
				// Handle collision between 2 creatures.
				std::cout << "creature collision" << std::endl;
				break;

			case ContactType::TERRAIN:
				// Handle collision between creature and terrain.
				std::cout << "terrain collision" << std::endl;
				break;
			}
		}
		else if (MouthPresent(contact, creatureA, other)) {
			if (creatureA == nullptr || other == nullptr) return;

			ContactType type = (ContactType)other->GetFilterData().categoryBits;

			switch (type) {
			case ContactType::TERRAIN:
				// Handle collision between creature and terrain.
				std::cout << "you can't eat terrain" << std::endl;
				break;
			}
		}

	}

	bool CreaturePresent(b2Contact* contact, Creature*& creature, b2Fixture*& other) {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		ContactType typeA = (ContactType)fixtureA->GetFilterData().categoryBits;
		ContactType typeB = (ContactType)fixtureB->GetFilterData().categoryBits;

		if (typeA == ContactType::CREATURE) {
			creature = (Creature*)fixtureA->GetUserData();
			other = fixtureB;
			return true;
		}

		if (typeB == ContactType::CREATURE) {
			creature = (Creature*)fixtureB->GetUserData();
			other = fixtureA;
			return true;
		}

		return false;
	}

	bool MouthPresent(b2Contact* contact, Creature*& creature, b2Fixture*& other)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		if (!fixtureA->IsSensor() && !fixtureB->IsSensor()) return false;

		ContactType typeA = (ContactType)fixtureA->GetFilterData().categoryBits;
		ContactType typeB = (ContactType)fixtureB->GetFilterData().categoryBits;

		if (typeA == ContactType::MOUTH) {
			creature = (Creature*)fixtureA->GetUserData();
			other = fixtureB;
			return true;
		}

		if (typeB == ContactType::MOUTH) {
			creature = (Creature*)fixtureB->GetUserData();
			other = fixtureA;
			return true;
		}

		return false;
	}

	void EndContact(b2Contact* contact) {


	}
};