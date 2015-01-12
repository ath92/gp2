#include "ofApp.h"
#include "Swarm.h"
#include <math.h>



    

//--------------------------------------------------------------
void Swarm::setup(WaveSurface * w){
	ws=w;
	numParticles = 1000;
	textureRes = 0;

	//Variables for the flocking algorithm
	influenceTarget = 0.02;
	wallDistanceTarget = 0.01;
	wallInfluenceTarget = 1;
	mouseInfluenceTarget = 0.003;
	repelStrengthTarget = 20;

	maxSpeedTarget = 0.015;

	randomnessTarget = 0.001;

	separationDistanceTarget = 0.7;
	neighborDistanceTarget = 2;
	crowdDistanceTarget = 5;

	//variables for drawing
	
	drawSizeTarget = 60;
	brightnessTarget = 1;
	opacityTarget = 0.5;
	redMultiplierTarget = 1.0;
	greenMultiplierTarget = 1.0;
	blueMultiplierTarget = 1.0;
	redTarget = 1.0;
	greenTarget = 0.1;
	blueTarget = 0.1;
	speedTarget = 1;
	
	//make sure the actual variables are close as well
	for(int i=0;i<10;i++){
		updateToTargets();
	}


	fs = false;
    
    // set defaults
    particleSize = 10.0;
    
    // load shaders
    position.load("","shaders/posUpdate.frag");
    
    velocity.load("","shaders/velUpdate.frag");
    
    // load ping-pong buffers
    // Seting the textures where the information ( position and velocity ) will be
    textureRes = (int)sqrt((float)numParticles);
    numParticles = textureRes * textureRes;
    
    // Make arrays of float pixels with position information
    
    float * pos = new float[numParticles*3];
    for (int x = 0; x < textureRes; x++){
        for (int y = 0; y < textureRes; y++){
            int i = textureRes * y + x;
            
            pos[i*3 + 0] = ofRandom(0.0, 1.0);
            pos[i*3 + 1] = ofRandom(0.0, 1.0);
            pos[i*3 + 2] = ofRandom(0.0, 1.0);
        }
    }
    
    posPingPong.allocate(textureRes, textureRes,GL_RGB32F);
    posPingPong.src->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
    posPingPong.dst->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
    
    delete [] pos;    // Delete the array
    
    
    // 2. Making arrays of float pixels with velocity information and the load it to a texture
    float * vel = new float[numParticles*3];
    for (int i = 0; i < numParticles; i++){
        vel[i*3 + 0] = ofRandom(-.001,.001);
        vel[i*3 + 1] = ofRandom(-.001,.001);
        vel[i*3 + 2] = ofRandom(-.001,.001);
    }
    // Load this information in to the FBO texture
    velPingPong.allocate(textureRes, textureRes,GL_RGB32F);
    velPingPong.src->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
    velPingPong.dst->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
    delete [] vel; // Delete the array



	
	//Billboards
	
	for(int n = 0; n< NUMBER_OF_TRAILS; n++){
		billboardContainers[n].getVertices().resize(numParticles);
		billboardContainers[n].getColors().resize(numParticles);
		billboardContainers[n].getNormals().resize(numParticles,ofVec3f(0));
	
		// ------------------------- billboard particles
		for (int i=0; i<numParticles; i++) {
		
			billboardContainers[n].getVertices()[i].set(ofRandom(-500, 500), 
														ofRandom(-500, 500), 
														ofRandom(-500, 500));
			ofColor color = ofColor(i%3*127,(i+1)%3*127,(i+2)%3*127,255);
			//color = ofColor::fromHsb(ofRandom(255),255,255,120);
			int col = ofRandom(255*brightness);
			color = ofColor(col*redMultiplier,col*greenMultiplier,col*blueMultiplier,255*opacity);
			billboardContainers[n].getColors()[i].set(color);
		
		}
	
	
		billboardContainers[n].setUsage( GL_DYNAMIC_DRAW );
		billboardContainers[n].setMode(OF_PRIMITIVE_POINTS);
	}
	//billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	//billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	
	// load the billboard shader
	// this is used to change the
	// size of the particle
	if(ofGetGLProgrammableRenderer()){
		billboardShader.load("shadersGL3/Billboard");
	}else{
		billboardShader.load("shadersGL2/Billboard");
	}
	
	// we need to disable ARB textures in order to use normalized texcoords
	ofDisableArbTex();
	texture.loadImage("dot.png");
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	glDepthMask(false); 
}

//--------------------------------------------------------------
void Swarm::update(){
	updateToTargets();
    velPingPong.dst->begin();
    ofClear(0);
    velocity.begin();
    velocity.setUniform1i("posWidth", velPingPong.src->getWidth());
    velocity.setUniform1i("posHeight", velPingPong.src->getWidth());
    velocity.setUniformTexture("backbuffer", velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
    velocity.setUniformTexture("posData", posPingPong.src->getTextureReference(), 1);      // passing the position information
    velocity.setUniformTexture("waveSurface", ws->derivativeTexture, 2);      // passing the position information
    
    
    // play with these to change your patterns
    velocity.setUniform1f("separationDistance", separationDistance);
    velocity.setUniform1f("neighborDistance", neighborDistance);
    velocity.setUniform1f("crowdDistance", crowdDistance);
    velocity.setUniform1f("surfaceHeight", width);
	velocity.setUniform1f("surfaceWidth", height);
	velocity.setUniform1f("mouseX", mouseVec.x);
    velocity.setUniform1f("mouseY", mouseVec.y);


	
    velocity.setUniform1f("influence", influence);
    velocity.setUniform1f("wallDistance", wallDistance);
    velocity.setUniform1f("wallInfluence", wallInfluence);
    velocity.setUniform1f("mouseInfluence", mouseInfluence);
	
    velocity.setUniform1f("repelStrength", repelStrength);
    velocity.setUniform1f("maxSpeed", maxSpeed);
    velocity.setUniform1f("randomness", randomness);
	

    
    // draw the source velocity texture to be updated
    velPingPong.src->draw(0, 0);
    
    velocity.end();
    velPingPong.dst->end();
    
    velPingPong.swap();
    
    
    // Position PingPong
    //
    // With the velocity calculated updates the position
    //
    posPingPong.dst->begin();
    ofClear(0);
    position.begin();
    position.setUniform1i("posWidth", velPingPong.src->getWidth());
    position.setUniform1f("speed", speed);
    position.setUniform1i("posHeight", velPingPong.src->getWidth());
    position.setUniformTexture("prevPosData", posPingPong.src->getTextureReference(), 0); // Previus position
    position.setUniformTexture("velData", velPingPong.src->getTextureReference(), 1);  // Velocity
    
    // draw the source position texture to be updated
    posPingPong.src->draw(0, 0);
    
    position.end();
    posPingPong.dst->end();
    
    posPingPong.swap();



}

//--------------------------------------------------------------
void Swarm::draw(){
	//draw glsl rendered swarm
    //renderFBO.draw(0,0, ofGetWidth(), ofGetHeight());

	float xm = ofGetWidth();
	float ym = ofGetHeight();
	float zm = 200;
	int zValue = 150;
	float zResolution = 5;

	posPingPong.dst->getTextureReference().readToPixels(positionPixels);
	velPingPong.dst->getTextureReference().readToPixels(velocityPixels);
	
	for(int x=0; x< positionPixels.getWidth(); x++){
		for(int y=0; y< positionPixels.getHeight(); y++){

			ofFloatColor col = positionPixels.getColor(x,y);
			ofFloatColor size = velocityPixels.getColor(x,y);

			
			//billboard textures
			
			float billboardSize = ofVec3f(size.r, size.g, size.b).length()*100;
			for(int n = NUMBER_OF_TRAILS-1; n > 0; n--){
				ofVec3f previous = billboardContainers[n-1].getVertex(y*positionPixels.getWidth() + x);
				billboardContainers[n].setVertex(y*positionPixels.getWidth() + x, previous); 
				billboardContainers[n].setNormal(y*positionPixels.getWidth()+x,ofVec3f(drawSize / sqrt(n) * billboardSize,0,0));
			}
			
			billboardContainers[0].setVertex(y*positionPixels.getWidth() + x, ofPoint(col.r*xm-xm/2,col.g*ym-ym/2,col.b*zm*zResolution+zValue)); 
			billboardContainers[0].setNormal(y*positionPixels.getWidth()+x,ofVec3f(drawSize * billboardSize,0,0));


			/*
			ofSetColor(255,255,255);
			//ofRect(col.r*xm,col.g*ym,0,1000*(size.r+size.g)+1,1000*(size.r+size.g)+1);
			ofLine(col.r*xm-xm/2, col.g*ym-ym/2, zValue, col.r*xm-size.r*xm-size.g/2*xm-xm/2, col.g*ym-size.g*ym-ym/2, zValue);
			ofLine(col.r*xm-size.r*xm-size.g/2*xm-xm/2, col.g*ym-size.g*ym-ym/2, zValue, col.r*xm-size.r*xm+size.g/2*xm-xm/2, col.g*ym-size.g*ym-ym/2, zValue);
			ofLine(col.r*xm-size.r*xm+size.g/2*xm-xm/2, col.g*ym-size.g*ym-ym/2, zValue, col.r*xm-xm/2, col.g*ym-ym/2, zValue);
			*/
		}
	}
	
	ofSetColor(255);

	

	billboardShader.begin();
	
	ofEnablePointSprites(); // not needed for GL3/4
	texture.getTextureReference().bind();
	
	for(int n = 0; n< NUMBER_OF_TRAILS; n++){
		billboardContainers[n].draw();
	}
	texture.getTextureReference().unbind();
	ofDisablePointSprites(); // not needed for GL3/4
	
	billboardShader.end();
	
}


void Swarm::setColors(){
	for(int n = 0; n< NUMBER_OF_TRAILS && n<(sizeof(billboardContainers)/sizeof(*billboardContainers)); n++){
		for (int i=0; i<numParticles; i++) {
			int col = ofRandom(255*brightness);
			ofColor color = ofColor(col*red*redMultiplier,col*green*greenMultiplier,col*blue*blueMultiplier,255*opacity);
			
			if(billboardContainers[n].getColors().size() < i+1) return;
			billboardContainers[n].getColors()[i].set(color);
		}
	}
}

void Swarm::updateToTargets(){
	//Variables for the flocking algorithm
	influence += (influenceTarget - influence) * animationSpeed;
	wallDistance += (wallDistanceTarget - wallDistance) * animationSpeed;
	wallInfluence += (wallInfluenceTarget - wallInfluence) * animationSpeed;
	mouseInfluence += (mouseInfluenceTarget - mouseInfluence) * animationSpeed;
	repelStrength += (repelStrengthTarget - repelStrength) * animationSpeed;
	maxSpeed += (maxSpeedTarget - maxSpeed) * animationSpeed;
	randomness += (randomnessTarget - randomness) * animationSpeed;
	separationDistance += (separationDistanceTarget - separationDistance) * animationSpeed;
	neighborDistance += (neighborDistanceTarget - neighborDistance) * animationSpeed;
	crowdDistance += (crowdDistanceTarget - crowdDistance) * animationSpeed;
	speed += (speedTarget - speed) * animationSpeed;

	//Variables for drawing things
	drawSize += (float)(drawSizeTarget - drawSize)*animationSpeed;
	brightness += (brightnessTarget - brightness)*animationSpeed;
	opacity += (opacityTarget - opacity)*animationSpeed;
	red += (redTarget - red)*animationSpeed;
	green += (greenTarget - green)*animationSpeed;
	blue += (blueTarget - blue)*animationSpeed;
	redMultiplier += (redMultiplierTarget - redMultiplier)*animationSpeed;
	greenMultiplier += (greenMultiplierTarget - greenMultiplier)*animationSpeed;
	blueMultiplier += (blueMultiplierTarget - blueMultiplier)*animationSpeed;

	setColors();
}