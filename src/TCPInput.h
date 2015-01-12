#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "People.h"

class TCPInput
{
public:
	void setup(People * people);
	void update();

	ofxTCPClient tcp;
	People * people;
};

