#include "PlaygroundTest.h"
#include "ofMain.h"
#include "ofApp.h"

PlaygroundTest::PlaygroundTest(){
	setupComplete = false;
}

void PlaygroundTest::setup(People * p){
	udpConnection.Create();
	udpConnection.Bind(9003);//Port 3199 for LEDGO floor
	udpConnection.SetNonBlocking(true);

	people = p;

	setupComplete = true;
}

#pragma push
#pragma pack(1)
struct Packet
{
	float x;
	float y;
	float weight;
	short zone;
};
#pragma pop

void PlaygroundTest::update(){
	if(!setupComplete) return;
	char udpMessage[3000];
	int messageLength = 0;
	while(messageLength != -1){
		messageLength = udpConnection.Receive(udpMessage,3000);
		if(messageLength != -1) cout << messageLength << endl;
	}

	//interface with people class

	//Lame version:
	//updatePeople();

	//Advanced version
	//updatePeopleAdvanced();
}

bool PlaygroundTest::hasWeights(){
	return (weights.size()>0);
}

void PlaygroundTest::updatePeople(){
	//first, remove all old people
	people->clear();

	//now, add all new people
	while(hasWeights()){
		ofVec3f back = popWeight();
		Person * p = people->addPerson();
		cout << ofGetWidth() << endl;
		p->setPosition(ofVec2f(back.x * (screenWidth / (float)floorWidth) , (back.y+30) * (screenHeight / (float)floorHeight)));
		cout << back << endl;
	}
}

void PlaygroundTest::updatePeopleAdvanced(){
	while(hasWeights()){
		ofVec3f back = popWeight();
		Person * p = people->addPerson();
		cout << ofGetWidth() << endl;
		p->setPosition(ofVec2f(back.x * (screenWidth / (float)floorWidth) , (back.y+30) * (screenHeight / (float)floorHeight)));
		cout << back << endl;
	}
}

ofVec3f PlaygroundTest::popWeight(){
	ofVec3f back = weights.back();
	weights.pop_back();
	return back;
}