#include "Person.h"


Person::Person(WaveSurface * ws)
{
	this->ws = ws;
}

void Person::update(){
	ws->applyForce(pos.x,pos.y);
}

void Person::setPosition(ofVec2f p){
	pos = p;
}