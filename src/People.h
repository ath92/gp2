#pragma once

#include "ofMain.h"
#include "Person.h"
#include "WaveSurface.h"

class People {

	public:
		Person * addPerson();
		void setup(WaveSurface * ws);
		void beforeUpdate();
		void update();
		void draw();
		void removePerson(Person * p);
		void movePerson(Person * p);
		void clear();
		void removeNotUpdated();

		Person * findByID(int id);

		list<Person *> people;
		WaveSurface * ws;

		//Behavior

		float energy;//average of energy of all people on the floor
		float proximity;//average distance of position vectors
		float organization;//average distance of velocity vectors

		void updateBehavior();
};