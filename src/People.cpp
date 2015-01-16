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
	updateBehavior();
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

void People::updateBehavior(){
	//get average distance between position vectors
	//get average distance between velocity vectors
	//get average energy of all people
	float totalEnergy = 0;
	float totalDistance = 0;
	for(auto person = begin(people); person != end(people); ++person){
		totalEnergy += (*person)->energy;
    }
	energy = totalEnergy / people.size();

	cout << "energy: " << energy << endl;
	cout << "organization: " << organization << endl;
	cout << "proximity: " << proximity << endl;
}