#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "WaveSurface.h"

class SurfaceStatus{
	public:
		void setup(WaveSurface *s);
		void load();

		void save(string name);

		
		void guiEvent(ofxUIEventArgs &e);

		
		ofxUISuperCanvas *gui;

		WaveSurface * surface;

		//status variables
		float first;

};