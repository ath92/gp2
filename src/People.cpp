#include "People.h"


void People::setup(WaveSurface * ws, FlockStatus * flockStatus, SurfaceStatus * surfaceStatus){
	this->ws = ws;
	energeticCalm = false;//start with calm
	organizedChaotic = false;//start with organized
	warmCold = false;//start with cold

	fs = flockStatus;
	ss = surfaceStatus;
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
			totalChaos += (*person)->direction.distance((*otherPerson)->direction);
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
			ss->gui->loadSettings("Calm_surface.xml");
			fs->gui->loadSettings("Calm_flock.xml");
		} else if(people.size() == 1){
			if(energy > energyThreshold){
				//change to energetic
				ss->gui->loadSettings("Calm_surface.xml");
				fs->gui->loadSettings("Calm_flock.xml");
			} else {
				//change to calm
				ss->gui->loadSettings("Calm_surface.xml");
				fs->gui->loadSettings("Calm_flock.xml");
			}
		} else{
			if(energy > energyThreshold){
				if(chaos > chaosThreshold){
					//change to chaotic
					ss->gui->loadSettings("Chaotic_surface.xml");
					fs->gui->loadSettings("Chaotic_flock.xml");
				} else {
					//chane to organized
					ss->gui->loadSettings("Organized_surface.xml");
					fs->gui->loadSettings("Organized_flock.xml");
				}
			} else {
				if(proximity > proximityThreshold){
					//change to cold
					ss->gui->loadSettings("Cold_surface.xml");
					fs->gui->loadSettings("Cold_flock.xml");
				} else {
					//chane to warm
					ss->gui->loadSettings("Warm_surface.xml");
					fs->gui->loadSettings("Warm_flock.xml");
				}
			}
		}
	}
}