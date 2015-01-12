#pragma once

#include "ofMain.h"
#include "WaveSurface.h"

class Person
{
public:
	Person(WaveSurface * ws);
	void update();
	void setPosition(ofVec2f p);
	ofVec2f pos;
	WaveSurface * ws;
};

