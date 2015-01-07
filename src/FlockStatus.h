#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Swarm.h"

class FlockStatus{
	public:
		void setup(Swarm *s);
		void load();

		void save(string name);

		
		void guiEvent(ofxUIEventArgs &e);

		
		ofxUISuperCanvas *gui;
		Swarm *swarm;

		//status variables
		float first;

};