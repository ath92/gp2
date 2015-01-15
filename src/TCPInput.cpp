#include "TCPInput.h"


void TCPInput::setup(People * p){
	this->people = p;
	tcp.setup("127.0.0.1", 9009);
}

void TCPInput::update(){
	if(tcp.isConnected()) {
        string str = tcp.receive(); // did anything come in
		cout << str << endl;
		
		std::vector<char> vect;

		std::stringstream ss(str);

		char c;

		while (ss >> c)
		{
			vect.push_back(c);

			if (ss.peek() == ','){
				ss.ignore();
				//we now have the int in the vector. 
				string intStr(vect.begin(),vect.end());
				cout << intStr << endl;
			}
		}

		
    }
}