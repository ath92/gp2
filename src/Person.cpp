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
}

void Person::beforeUpdate(){
	assigned = false;
}

void Person::update(){
	timeoutCounter++;
	ws->applyForce(pos.x,pos.y);
	energy *= energyDamping;
	cout << "energy: " << energy << endl;
}

void Person::draw(){
	ofSetColor(color);
	ofCircle(ofPoint(pos.x,pos.y, 0), 20);
	ofSetColor(color.invert());
	ofLine(ofPoint(pos.x,pos.y, 0), ofPoint(pos.x+direction.x*3,pos.y+direction.y*3, 0));
	ofSetColor(255);
}

void Person::setPosition(ofVec2f p){
	energy = p.distance(pos) > energy ? p.distance(pos) : energy;
	direction = direction * directionDamping + (p-pos) * (1-directionDamping);
	timeoutCounter = 0;
	assigned = true;
	pos = p;
}

void Person::setID(int n){
	id = n;
}