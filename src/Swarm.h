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
		float influence;
		float wallDistance;
		float wallInfluence;
		float mouseInfluence;
		float repelStrength;

		float maxSpeed;

		float randomness;

		float separationDistance;
		float neighborDistance;
		float crowdDistance;

		float speed;

		//Variables for drawing things
		int drawSize;
		float brightness, opacity, red, green, blue, redMultiplier, greenMultiplier, blueMultiplier;
		WaveSurface * ws;
};