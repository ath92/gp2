#include "People.h"


void People::setup(WaveSurface * ws){
	this->ws = ws;
	energeticCalm = false;//start with calm
	organizedChaotic = false;//start with organized
	warmCold = false;//start with cold
}

void People::beforeUpdate(){
	for(auto person = begin(people); person != end(people); ++person){
		(*person)->beforeUpdate();
    }
}

void People::update(){
	updateBehavior();
	for(auto person = begin(people); person != end(people); ++person){
		(*person)->update();
    }
	removeNotUpdated();

	updateState();
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

void People::updateBehavior(){
	//get average distance between position vectors

	//get average distance between velocity vectors
	//get average energy of all people
	float totalEnergy = 0;
	float totalDistance = 0;
	float totalOrganization = 0;
	for(auto person = begin(people); person != end(people); ++person){
		totalEnergy += (*person)->energy;
		for(auto otherPerson = begin(people); otherPerson != end(people); ++otherPerson){
			totalDistance += (*person)->pos.distance((*otherPerson)->pos);
			totalOrganization += (*person)->direction.distance((*otherPerson)->direction);
		}
    }
	proximity = totalDistance / (people.size() * people.size());
	energy = totalEnergy / people.size();
	organization = (totalOrganization / (people.size() * people.size()) +100/energy) * 100;//Divided by energy to assure that the state is only entered when people are actually moving. *100 to easily identify
	cout << "energy: " << energy << endl;
	cout << "organization: " << organization << endl;
	cout << "proximity: " << proximity << endl;
}

void People::updateState(){
	float energyDifference = abs(energy - energyThreshold);
	float proximityDifference = abs(proximity - proximityThreshold);
	float organizationDifference = abs(organization - organizationThreshold);
}