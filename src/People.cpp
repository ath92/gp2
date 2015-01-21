#include "People.h"


void People::setup(WaveSurface * ws, FlockStatus * flockStatus, SurfaceStatus * surfaceStatus){
	this->ws = ws;
	energeticCalm = false;//start with calm
	organizedChaotic = false;//start with organized
	warmCold = false;//start with cold

	fs = flockStatus;
	ss = surfaceStatus;

	currentState = 3;//start with calm.
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
	float totalChaos = 0;
	for(auto person = begin(people); person != end(people); ++person){
		totalEnergy += (*person)->energy;
		for(auto otherPerson = begin(people); otherPerson != end(people); ++otherPerson){
			totalDistance += (*person)->pos.distance((*otherPerson)->pos);
			totalChaos += abs((*person)->direction.length() - (*otherPerson)->direction.length());
		}
    }
	energy = totalEnergy / people.size();
	proximity = totalDistance / (people.size() * people.size());//Divide by energy because we only want to track this if people aren't moving. 
	float currentChaos = totalChaos / (people.size() * people.size()) * energy;//Multiplied by energy because we only want chaos when there is energy.
	chaos = currentChaos > chaos ? currentChaos : chaos;
	chaos *= chaosDamping;
	cout << "energy: " << energy << endl;
	cout << "chaos: " << chaos << endl;
	cout << "proximity: " << proximity << endl;
	updateState();
}

void People::updateState(){
	counter++;
	
	if(counter%characteristicTime == 0){
		//update status;
		if(people.size() == 0){
			//change to calm
			currentState = 3;
		} else if(people.size() == 1){
			if(energy > energyThreshold){
				//change to energetic
				currentState = 0;
			} else {
				//change to calm
				currentState = 3;
			}
		} else{
			if(energy > multiEnergyThreshold){
				if(chaos > chaosThreshold){
					//change to chaotic
					currentState = 1;
				} else {
					//chane to organized
					currentState = 4;
				}
			} else {
				if(proximity > proximityThreshold){
					//change to cold
					currentState = 2;
				} else {
					//chane to warm
					currentState = 5;
				}
			}
		}
		ss->gui->loadSettings(states[currentState] + "_surface.xml");
		fs->gui->loadSettings(states[currentState] + "_flock.xml");
	}


	
}