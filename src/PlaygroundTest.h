#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "People.h"

class PlaygroundTest
{
public:
	ofxUDPManager udpConnection;
	vector<ofVec3f> weights;
	PlaygroundTest();
	void setup(People * p);
	void update();
	bool hasWeights();

	void updatePeople();
	void updatePeopleAdvanced();
	ofVec3f popWeight();

	People * people;

	bool setupComplete;
};