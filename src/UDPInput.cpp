#include "UDPInput.h"
#include "ofMain.h"
#include "ofApp.h"

UDPInput::UDPInput(){
	udpConnection.Create();
	udpConnection.Bind(3199);//Port 3199 for LEDGO floor
	udpConnection.SetNonBlocking(true);
	setupComplete = false;
	basic = true;
}

void UDPInput::setup(People * p){
	people = p;
	setupComplete = true;
}

#pragma push
#pragma pack(1)
struct Packet
{
	float x;
	float y;
	float weight;
	short zone;
};
#pragma pop

void UDPInput::update(){
	if(!setupComplete) return;
	char udpMessage[3000];
	int messageLength = 0;
	while(messageLength != -1){
		messageLength = udpConnection.Receive(udpMessage,3000);
		if(messageLength != -1){
			Packet packet;
			unsigned short numPackets;
			memcpy(&numPackets,udpMessage,sizeof(unsigned short));
			char *s=udpMessage+2;

			for(int i=0;i<numPackets;i++)
			{
				memcpy(&packet,s,sizeof(Packet));
				Weight w;
				w.weight = ofVec3f(packet.x* (screenWidth / (float)floorWidth), packet.y* (screenHeight / (float)floorHeight), packet.weight);
				w.assigned = false;
				if(packet.weight!=0) weights.push_back(w);
				s+=sizeof(Packet);
			}
		}
	}

	//interface with people class

	//Lame version:
	if(basic) updatePeople();

	//Advanced version
	if(!basic) updatePeopleAdvanced();
}

bool UDPInput::hasWeights(){
	return (weights.size()>0);
}

void UDPInput::updatePeople(){
	//first, remove all old people
	people->clear();

	//now, add all new people
	
	while(hasWeights()){
		Weight w = popWeight();
		ofVec3f back = w.weight;
		Person * p = people->addPerson();
		p->setPosition(ofVec2f(back.x , back.y));
		//cout << back << endl;
	}
}

void UDPInput::updatePeopleAdvanced(){
	people->beforeUpdate();

	list<Person*> currentPeople;
	for(auto person = begin(people->people); person != end(people->people); ++person){
		currentPeople.push_back((*person));//get pointers to weights
	}

	list<Weight *> currentWeights;
	for(auto weight = begin(weights); weight != end(weights); ++weight){
		currentWeights.push_back(&(*weight));//get pointers to weights
	}

	matchPeopleToWeights(currentWeights, currentPeople);
}

void UDPInput::matchPeopleToWeights(list<Weight *> currentWeights, list<Person*> currentPeople){
	//cout << "people: " << currentPeople.size() << " weights: " << currentWeights.size() << endl;
	weights.clear();
	if(currentPeople.size() == 0 && currentWeights.size() == 0){
		return;
		//nothing else left to do.
	}else if(currentWeights.size() > 0 && currentPeople.size() > 0){
		//there are weights and people. Assign weights to the right people.
		for(auto person = begin(currentPeople); person != end(currentPeople); ++person){
			float closestDistance;
			int counter = 0;
			Weight * closestWeight = NULL;
			for(auto weight = begin(currentWeights); weight != end(currentWeights); ++weight){
				if(counter == 0){
					closestDistance = ofVec2f((*weight)->weight.x,(*weight)->weight.y).distance(ofVec2f((*person)->pos.x, (*person)->pos.y));
					closestWeight = (*weight);
				} else {
					float currentDistance = ofVec2f((*weight)->weight.x,(*weight)->weight.y).distance(ofVec2f((*person)->pos.x, (*person)->pos.y));
					if(currentDistance < closestDistance){
						closestWeight = (*weight);
					}
				}
			}
			
			if(closestWeight != NULL){
				//closest weight has been found.
				if(!closestWeight->assigned){
					//assign person to weight and vice versa.
					closestWeight->person = (*person);
					closestWeight->assigned = true;

					(*person)->setPosition(ofVec2f(closestWeight->weight.x, closestWeight->weight.y));

				} else {
					//check which person is closer
					Person * firstPerson = closestWeight->person;
					Person * secondPerson = (*person);
				
					//One person has to be unassigned.unassign both, as setPosition will reassign the right one.
					firstPerson->assigned = false;
					secondPerson->assigned = false;

					closestWeight->person = findClosestPersonToWeight(closestWeight->weight, (*person), closestWeight->person);
					closestWeight->person->setPosition(ofVec2f(closestWeight->weight.x, closestWeight->weight.y));
				}
			}
			
		}
		
	} else if(currentWeights.size() > 0 && currentPeople.size() == 0){
		//more weights than people

		
		list<Person*> allPeople;		
		for(auto person = begin(people->people); person != end(people->people); ++person){
			allPeople.push_back((*person));//get pointers to weights
		}

		
		for(auto weight = begin(currentWeights); weight != end(currentWeights); ++weight){
			//go through all the remaining weights

			
			ofVec2f weightPosition = ofVec2f((*weight)->weight.x, (*weight)->weight.y);
			for(auto person = begin(allPeople); person != end(allPeople); ++person){
				//if <condition for it to belong to a person>, assign this weight to person
				//Note: assigns weight to the first person that matches condition. Should add code to find the closest person.
				float distance = (*person)->pos.distance( weightPosition );
				cout << distance << " distance" << endl;
				if(distance < samePersonDistance) {
					ofVec2f averagePosition, personPosition;
					personPosition = (*person)->pos;
					averagePosition = (personPosition + weightPosition)/2;
					(*person)->setPosition(averagePosition);
					(*weight)->assigned = true;
				}
			}
			if(!(*weight)->assigned){//there was no person nearby
				Person * newPerson = people->addPerson();
				newPerson->setPosition(weightPosition);
			}
		}
	} else if(currentPeople.size() > 0 && currentWeights.size() == 0){
		//more people than weights
		//this shouldn't be possible, so remove remaining people
		//people->removeNotUpdated();
		//no more people, no more weights; return
		return;
	}

	//handle remaining 
	list<Weight *> newWeights;
	list<Person *> newPeople;
	
	for(auto person = begin(currentPeople); person != end(currentPeople); ++person){
		if(!(*person)->assigned) newPeople.push_back((*person));
	}

	for(auto weight = begin(currentWeights); weight != end(currentWeights); ++weight){
		if(!(*weight)->assigned) newWeights.push_back((*weight));
	}

	matchPeopleToWeights(newWeights, newPeople);
}

Person * UDPInput::findClosestPersonToWeight(ofVec3f weight, Person * firstPerson, Person * secondPerson){
	ofVec2f weightPos = ofVec2f(weight.x, weight.y);
	float distanceToFirst = weightPos.distance(ofVec2f(firstPerson->pos.x, firstPerson->pos.y));
	float distanceToSecond = weightPos.distance(ofVec2f(secondPerson->pos.x, secondPerson->pos.y));
	if(distanceToFirst < distanceToSecond) {
		return firstPerson;
	} else {
		return secondPerson;
	}
}

Weight UDPInput::popWeight(){
	Weight back = weights.back();
	weights.pop_back();
	return back;
}