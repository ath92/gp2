#pragma once

#include "ofMain.h"
#include "pingPongBuffer.h"
#include "WaveSurface.h"

#define NUMBER_OF_TRAILS 16


class Swarm {

	public:
		void setup(WaveSurface * w);
		void update();
		void draw();

		void setColors();
    
        // shaders
        ofShader velocity;
        ofShader position;
    
        // ping-pong buffers for position and velocity
        pingPongBuffer posPingPong;
        pingPongBuffer velPingPong;
    
        // parameters for flocking
        float maxVelocity;
        float maxForce;
    
        // size of circles
        float particleSize;

		//pixels to draw the boids from
		ofFloatPixels positionPixels, velocityPixels;

		//drawing options
		bool fs;

		ofVec2f mouseVec;

		
		// billboard particles
		
		ofShader billboardShader;
		ofImage texture;
		
		ofVboMesh billboardContainers[NUMBER_OF_TRAILS];

		//Status variables
		int numParticles;
		int textureRes;



		//Variables for the flocking algorithm
		float influence,wallDistance,wallInfluence,mouseInfluence,repelStrength,maxSpeed,randomness,separationDistance,neighborDistance,crowdDistance,speed;

		//Variables for drawing things
		int drawSize;
		float brightness, opacity, red, green, blue, redMultiplier, greenMultiplier, blueMultiplier;

		

		//Targets for the flocking algorithm
		float influenceTarget,wallDistanceTarget,wallInfluenceTarget,mouseInfluenceTarget,repelStrengthTarget,maxSpeedTarget,randomnessTarget,separationDistanceTarget,neighborDistanceTarget,crowdDistanceTarget,speedTarget;

		//Targets for drawing things
		int drawSizeTarget;
		float brightnessTarget, opacityTarget, redTarget, greenTarget, blueTarget, redMultiplierTarget, greenMultiplierTarget, blueMultiplierTarget;

		//update to targets
		void updateToTargets();


		WaveSurface * ws;
};