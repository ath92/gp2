#pragma once

#include "ofMain.h"
#include "People.h"

const int logInterval = 1;//interval in seconds

class StateLogger
{
public:
	void setup(People * p);

	void update();

	People * people;

	ofFile file;

	string fileName;
	string log;

	int previousTime;

};

