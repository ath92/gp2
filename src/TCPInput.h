#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "People.h"

struct Tracker{
	int x, y, z, id;
};

class TCPInput
{
public:
	void setup(People * people);
	void update();

	ofxTCPClient tcp;
	People * people;

	bool basic;

	vector<Tracker> trackers;
};

