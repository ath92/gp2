#pragma once

#include "ofMain.h"
#include "Person.h"
#include "WaveSurface.h"

class People {

	public:
		Person * addPerson();
		void setup(WaveSurface * ws);
		void update();
		void removePerson(Person * p);
		void movePerson(Person * p);
		void clear();

		//implement tracking

		list<Person *> people;
		WaveSurface * ws;

};