#include "TCPInput.h"


void TCPInput::setup(People * p){
	this->people = p;
	tcp.setup("127.0.0.1", 9009);
}

void TCPInput::update(){
	if(tcp.isConnected()) {
        string str = tcp.receive(); // did anything come in
		cout << str << endl;
    }
}