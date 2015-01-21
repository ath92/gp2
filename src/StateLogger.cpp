#include "StateLogger.h"


void StateLogger::setup(People * p)
{
	people = p;
	fileName = to_string(ofGetUnixTime());
	previousTime = ofGetUnixTime();
}

void StateLogger::update(){
	if(ofGetUnixTime() >= previousTime + logInterval){
		previousTime = ofGetUnixTime();
		file.open(fileName + ".txt",ofFile::WriteOnly);  

		log += to_string(ofGetUnixTime()) + " " + to_string(people->currentState) + "\n\r";
		file << log; 

		file.close();
	}
}

