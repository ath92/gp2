#include "Person.h"


Person::Person(WaveSurface * ws)
{
	this->ws = ws;
	timeoutCounter = 0;
	color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

void Person::beforeUpdate(){
	assigned = false;
}

void Person::update(){
	timeoutCounter++;
	ws->applyForce(pos.x,pos.y);
}

void Person::draw(){
	ofSetColor(color);
	ofCircle(ofPoint(pos.x,pos.y, 0), 20);
	ofSetColor(255);
}

void Person::setPosition(ofVec2f p){
	timeoutCounter = 0;
	assigned = true;
	pos = p;
}

void Person::setID(int n){
	id = n;
}