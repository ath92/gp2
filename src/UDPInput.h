#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "People.h"

const int samePersonDistance = 300;
struct Weight{
	ofVec3f weight;
	Person * person;
	bool assigned;
};

class UDPInput
{
public:
	ofxUDPManager udpConnection;
	vector<Weight> weights;
	UDPInput();
	void setup(People * p);
	void update();
	bool hasWeights();

	void updatePeople();
	void updatePeopleAdvanced();
	void matchPeopleToWeights(list<Weight *> currentWeights, list<Person*> currentPeople);
	Person * findClosestPersonToWeight(ofVec3f weight, Person * firstPerson, Person * secondPerson);
	Weight popWeight();

	People * people;
	bool basic;
	bool setupComplete;
};
