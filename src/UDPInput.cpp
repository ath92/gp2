#include "UDPInput.h"
#include "ofMain.h"
#include "ofApp.h"

UDPInput::UDPInput(){
	udpConnection.Create();
	udpConnection.Bind(3199);//Port 3199 for LEDGO floor
	udpConnection.SetNonBlocking(true);
	setupComplete = false;
}

void UDPInput::setup(People * p){
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

void UDPInput::update(){
	if(!setupComplete) return;
	char udpMessage[3000];
	int messageLength = 0;
	while(messageLength != -1){
		messageLength = udpConnection.Receive(udpMessage,3000);
		if(messageLength != -1){
			Packet packet;
			unsigned short numPackets;
			memcpy(&numPackets,udpMessage,sizeof(unsigned short));
			char *s=udpMessage+2;

			for(int i=0;i<numPackets;i++)
			{
				memcpy(&packet,s,sizeof(Packet));
				if(packet.weight!=0) weights.push_back(ofVec3f(packet.x,packet.y,packet.weight));
				s+=sizeof(Packet);
			}
			/*cout << "received " << messageLength << endl;
			for(int i=0; i<messageLength/14; i++){
				float x,y,w;
				char xArr[] = {udpMessage[2], udpMessage[3], udpMessage[4], udpMessage[5]};
				memcpy(&x, &xArr, sizeof(x));
		
				char yArr[] = {udpMessage[6], udpMessage[7], udpMessage[8], udpMessage[9]};
				memcpy(&y, &yArr, sizeof(y));
		
				char wArr[] = {udpMessage[10], udpMessage[11], udpMessage[12], udpMessage[13]};
				memcpy(&w, &wArr, sizeof(w));

				if(w!=0){
					weights.push_back(ofVec3f(x,y,w));
				}
			}*/
		}
	}

	//interface with people class

	//Lame version:
	updatePeople();

	//Advanced version
	//updatePeopleAdvanced();
}

bool UDPInput::hasWeights(){
	return (weights.size()>0);
}

void UDPInput::updatePeople(){
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

void UDPInput::updatePeopleAdvanced(){
	while(hasWeights()){
		ofVec3f back = popWeight();
		Person * p = people->addPerson();
		cout << ofGetWidth() << endl;
		p->setPosition(ofVec2f(back.x * (screenWidth / (float)floorWidth) , (back.y+30) * (screenHeight / (float)floorHeight)));
		cout << back << endl;
	}
}

ofVec3f UDPInput::popWeight(){
	ofVec3f back = weights.back();
	weights.pop_back();
	return back;
}