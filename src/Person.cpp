#include "Person.h"


Person::Person(WaveSurface * ws)
{
	this->ws = ws;
	timeoutCounter = 0;
	color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));

	//parameters for behavior tracking
	energyDamping = 0.98;
	energy = 0;

	directionDamping = 0.98;
	direction = ofVec2f(0,0);
	
	newPerson = true;
}

void Person::beforeUpdate(){
	assigned = false;
}

void Person::update(){
	timeoutCounter++;
	ws->applyForce(pos.x,pos.y);
	energy *= energyDamping;
}

void Person::draw(){
	ofSetColor(color);
	ofCircle(ofPoint(pos.x,pos.y, 0), 20);
	ofLine(ofPoint(pos.x,pos.y, 0), ofPoint(pos.x+direction.x*3,pos.y+direction.y*3, 0));
	ofSetColor(255);
}

void Person::setPosition(ofVec2f p){
	if(p.x > 0 && p.x < ofGetWidth() && p.y > 0 && p.y < ofGetHeight()){
		energy = p.distance(pos) > energy ? p.distance(pos) : energy;
		direction = direction * directionDamping + (p-pos) * (1-directionDamping);
		timeoutCounter = 0;
		assigned = true;
		pos = p;
	} else {
		newPerson = true;
	}
	//when a new person enters the system, their energy should not be initialized as they have no previous position and their velocity can therefore not be calculated.
	if(newPerson){
		cout << "new person!" << endl;
		newPerson = false;
		direction = ofVec2f(0,0);
		energy = 0;
	}
}

void Person::setID(int n){
	id = n;
}