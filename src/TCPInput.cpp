#include "TCPInput.h"


void TCPInput::setup(People * p){
	this->people = p;
	tcp.setup("0.0.0.0", 9009);
}

void TCPInput::update(){
	if(tcp.isConnected()) {
        string str = tcp.receive(); // did anything come in
    }
}