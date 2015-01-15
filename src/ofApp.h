#pragma once

#include "ofMain.h"
#include "Swarm.h"
#include "WaveSurface.h"
#include "VideoRecorder.h"
#include "FlockStatus.h"
#include "SurfaceStatus.h"
#include "People.h"
#include "Playground.h"
#include "UDPInput.h"
#include "TCPInput.h"
#include "PlaygroundTest.h"

const int floorWidth = 192;
const int floorHeight = 192;

const int screenWidth = 900;
const int screenHeight = 900;

const float animationSpeed = 0.05;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		Swarm swarm;
		WaveSurface surface;

		ofEasyCam cam, cam2;

		FlockStatus flockStatus;
		SurfaceStatus surfaceStatus;

		ofFbo fbo;

		//Saving to xml
		
		ofxUISuperCanvas *saveGUI;
		ofxUIRadio *radio;
		vector<string> saveNames;

		float xFactor,yFactor;//scaling to floor
		bool scale;

		People people;
		Playground playground;
		//UDPInput connection;
		TCPInput connection;
		//PlaygroundTest connection;
		ofVideoPlayer video;
};
