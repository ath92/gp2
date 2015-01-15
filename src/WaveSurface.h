#pragma once

#include "ofMain.h"


const int width = 100;
const int height = 100;

class WaveSurface {

	public:
		void setup();
		void update();
		void draw();
		

		void applyForce(float x, float y);
		void applySuddenForce(float x, float y);
		void releaseSuddenForce(float x, float y);
		float avgDelta(int x, int y);

		void smoothDerivative(int smooth);

		ofEasyCam cam;
		ofMesh mesh;
		ofLight light;
		
		ofVec2f scale;
		ofVec2f mouse;
		
		float grid[width*height];
		float offset[width*height];
		float deltagrid[width*height];
		float derivativex[width*height];
		float derivativey[width*height];

		ofTexture derivativeTexture;
		ofPixels derivativePixels;
		
		bool staystill;
		bool drawLines;

		//behavioral variables
		float zMultiplier, damping, forceStrength, influence;

		//behavioral targets
		float zMultiplierTarget, dampingTarget, forceStrengthTarget, influenceTarget;

		//aesthetic variables
		float random, colorBrightness, opacity, opacityMultiplier, redMultiplier, greenMultiplier, blueMultiplier, red, green, blue;

		//aesthetic targets
		float randomTarget, colorBrightnessTarget, opacityTarget, opacityMultiplierTarget, redMultiplierTarget, greenMultiplierTarget, blueMultiplierTarget, redTarget, greenTarget, blueTarget;

		//update towards targets
		void updateToTargets();

		//plaatje
		ofPixels pix;
		ofTexture tex;
};