#include "People.h"


void People::setup(WaveSurface * ws){
	this->ws = ws;
}

void People::beforeUpdate(){
	for(auto person = begin(people); person != end(people); ++person){
		(*person)->beforeUpdate();
    }
}

void People::update(){
	for(auto person = begin(people); person != end(people); ++person){
		(*person)->update();
    }
	removeNotUpdated();
}

void People::draw(){
	for(auto person = begin(people); person != end(people); ++person){
		(*person)->draw();
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

void People::removeNotUpdated(){
	list<Person *> newPeople;
	for(auto person = begin(people); person != end(people); ++person){
		if((*person)->timeoutCounter < 30){
			newPeople.push_back((*person));
		}
    }
	people = newPeople;
}

Person * People::findByID(int id){
	for(auto person = begin(people); person != end(people); ++person){
		if((*person)->id == id){
			return (*person);
		}
    }
	Person * p = addPerson();
	p->setID(id);
	return p;
}