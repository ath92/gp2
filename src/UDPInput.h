#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "People.h"
#ifndef UDPINPUT
#define UDPINPUT

class UDPInput
{
public:
	ofxUDPManager udpConnection;
	vector<ofVec3f> weights;
	UDPInput();
	void setup(People * p);
	void update();
	bool hasWeights();

	void updatePeople();
	void updatePeopleAdvanced();
	ofVec3f popWeight();

	People * people;

	bool setupComplete;
};
#endif