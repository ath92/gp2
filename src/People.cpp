#include "People.h"


void People::setup(WaveSurface * ws){
	this->ws = ws;
}

void People::update(){
	for(auto it = begin(people); it != end(people); ++it){
		(*it)->update();
    }
}

Person * People::addPerson(void)
{
	Person * p = new Person(ws);
	people.push_back(p);
	return p;
}

void People::clear(){
	people.clear();
}


void People::removePerson(Person * p)
{
	people.remove(p);
}