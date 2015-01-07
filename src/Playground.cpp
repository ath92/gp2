#include "Playground.h"


Playground::Playground(void)
{
	//tcp.setup("130.89.243.9", 9003);
}

void Playground::update()
{
    if(tcp.isConnected()) {
        string str = tcp.receive(); // did anything come in
		cout << str << endl;
    }
}

