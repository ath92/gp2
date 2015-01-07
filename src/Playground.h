#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class Playground
{
public:
	Playground(void);
	void update();

	ofxTCPClient tcp;
};

