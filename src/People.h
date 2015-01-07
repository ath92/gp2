#pragma once

#include "ofMain.h"
#include "Person.h"


class People {

	public:
		Person * addPerson();
		void removePerson(Person * p);
		void movePerson(Person * p);

		//implement tracking

		list<Person *> people;

};