#include "TCPInput.h"


const int trackerWidth = 46000;
const int trackerHeight = 54000;

void TCPInput::setup(People * p){
	this->people = p;
	tcp.setup("127.0.0.1", 9009);
}

void TCPInput::update(){
	//check if setup was initialized
	if(tcp.isConnected()) {
		//empty old trackers
		trackers.clear();

		//see if any new data comes in
        string s = tcp.receiveRaw();
        if(s.length() > 0){
			//cout << s.length() << endl;
			//cout << s;

			//loop through string, comma delimiter

			std::vector<int> vect;

			std::stringstream ss(s);

			int i;

			while (ss >> i)
			{
				vect.push_back(i);

				if (ss.peek() == ',')
					ss.ignore();
			}

			int counter = 0;
			for(auto value = begin(vect); value != end(vect); ++value){
				if(counter%4 == 0){
					Tracker currentTracker;
					currentTracker.id = (*value);
					trackers.push_back(currentTracker);
				} else if(counter%4 == 1){
					Tracker * currentTracker = &trackers.back();
					currentTracker->x = (*value);
				} else if(counter%4 == 2){
					Tracker * currentTracker = &trackers.back();
					currentTracker->y = (*value);
				} else if(counter%4 == 3){
					Tracker * currentTracker = &trackers.back();
					currentTracker->z = (*value);
				}
				//cout << (*value) << endl;
				counter++;
			}

		}
		//loop through trackers, update people.
		//people->clear();
		for(auto tracker = begin(trackers); tracker != end(trackers); ++tracker){
			Person * p = people->findByID((*tracker).id);
			float factoredX = ofGetWidth() - ((*tracker).x+6000) *ofGetWidth()/(float)trackerWidth;
			float factoredY = ((*tracker).y+40000) *ofGetHeight()/(float)trackerHeight;
			//invert axes for smartxp setup and do some other things differently
			factoredX = ((*tracker).y+41000) *ofGetWidth()/(float)trackerHeight;
			factoredY = ((*tracker).x+12500) *ofGetHeight()/(float)60000;
			p->setPosition(ofVec2f(factoredX , factoredY));//update factors.
		}
    }
	
}