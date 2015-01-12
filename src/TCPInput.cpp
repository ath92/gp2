#include "TCPInput.h"


void TCPInput::setup(People * p){
	this->people = p;
	tcp.setup("130.89.243.9", 9003);
}

void TCPInput::update(){
	if(tcp.isConnected()) {
        string str = tcp.receive(); // did anything come in
    }
}