#pragma once

#include "ofMain.h"
#include "WaveSurface.h"

class Person
{
public:
	Person(WaveSurface * ws);
	void beforeUpdate();
	void update();
	void draw();
	void setPosition(ofVec2f p);
	void setID(int n);
	ofVec2f pos;
	WaveSurface * ws;

	int timeoutCounter;

	bool assigned;

	ofColor color;

	int id;
	bool newPerson;

	//Behavior tracking

	float energy;
	float energyDamping;

	ofVec2f direction;
	float directionDamping;

};

