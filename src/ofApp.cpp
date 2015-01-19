#include "ofApp.h"

bool fs;
float mouseX;
float mouseY;

//--------------------------------------------------------------
void ofApp::setup(){
	surface.setup();
	swarm.setup(&surface);
	fs = false;

	flockStatus.setup(&swarm);
	surfaceStatus.setup(&surface);

	//setup people tracking
	people.setup(&surface);
	//add one person to arbitrary position for testing purposes
	//Person * p = people.addPerson();
	//p->setPosition(ofVec2f(1000,500));

	
	ofSetFrameRate(60);
	
	saveNames.push_back("Energetic");
	saveNames.push_back("Chaotic");
	saveNames.push_back("Abrupt");
	saveNames.push_back("Cold");
	saveNames.push_back("Calm");
	saveNames.push_back("Organized");
	saveNames.push_back("Elegant");
	saveNames.push_back("Warm");

	saveGUI = new ofxUISuperCanvas("Save to");

	saveGUI->addSpacer();
	
	radio = saveGUI->addRadio("Characteristic", saveNames, OFX_UI_ORIENTATION_VERTICAL);
    saveGUI->setPosition(212*2, 0);

	//draw to fbo to be able to scale afterwards
	fbo.allocate(ofGetWidth(), ofGetHeight());
	cout << xFactor << endl;
	scale = true;
	xFactor = 1;
	yFactor = 1;
	ofSetBackgroundAuto(false);


	//initially hide UI
		
	surfaceStatus.gui->toggleVisible();
	flockStatus.gui->toggleVisible();
	saveGUI->toggleVisible();

	//Load Calm to start with:	
	surfaceStatus.gui->loadSettings("Cold_surface.xml");
	flockStatus.gui->loadSettings("Cold_flock.xml");


	//load video
	//video.loadMovie("movie.mp4");
}

//--------------------------------------------------------------
void ofApp::update(){
	counter++;

	if(counter%2==1) return;//60fps test

	connection.update();
	people.update();
	swarm.update();
	surface.update();
	//surface.applyForce(mouseX,mouseY);
	//surface.applyForce(ofGetWidth()-mouseX,ofGetHeight()-mouseY);
	Person * mousePerson = people.findByID(-1);
	mousePerson->setPosition(ofVec2f(mouseX, mouseY));
	Person * mousePerson2 = people.findByID(-2);
	mousePerson2->setPosition(ofVec2f(ofGetWidth()-mouseX, mouseY));
	//video.update();
	//post.init(ofGetWidth(), ofGetHeight());
	//post.createPass<BloomPass>();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.setTarget(ofVec3f(0,0,0));
	ofSetWindowTitle(to_string(ofGetFrameRate()));

	ofDisableBlendMode();

	ofSetColor(0,0,0,10);
	ofRect(0,0,ofGetWidth(),ofGetHeight());

	fbo.begin();
	ofClear(0);
	cam.begin();
	ofEnableBlendMode ( OF_BLENDMODE_ADD ) ;  
	surface.draw();
	swarm.draw();
	cam.end();
	people.draw();
	fbo.end();
	ofScale(xFactor,yFactor);
	fbo.draw(0,0,ofGetWidth(),ofGetHeight());
	ofScale(1/xFactor,1/yFactor);//scale back for interface

	//video.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='f'){
		ofToggleFullscreen();
	} else if(key=='h'){
		surfaceStatus.gui->toggleVisible();
		flockStatus.gui->toggleVisible();
		saveGUI->toggleVisible();
	} else if(key=='x'){
		string name = radio->getActiveName();
		if(name!=""){
			surfaceStatus.gui->saveSettings(name+"_surface.xml");
			flockStatus.gui->saveSettings(name+"_flock.xml");
			cout << "saved to: " << name << ".xml" << endl;
		} else {
			cout << "none active!" << endl;
		}
	} else if(key=='c'){
		string name = radio->getActiveName();
		if(name!=""){
			surfaceStatus.gui->loadSettings(name+"_surface.xml");
			flockStatus.gui->loadSettings(name+"_flock.xml");
			cout << "Loaded " << name << ".xml" << endl;
		} else {
			cout << "none active!" << endl;
		}
	} else if(key=='l'){
		if(scale){
			xFactor = (float)floorWidth/ofGetWidth();
			yFactor = (float)floorHeight/ofGetHeight();
		} else {
			xFactor = 1;
			yFactor = 1;
		}
		scale = !scale;
	} else if(key=='w'){
		surface.drawLines = !surface.drawLines;
	} else if(key=='i'){
		//setup Connection
		connection.setup(&people);
	} else if(key=='o'){
		//setup Connection
		connection.basic = !connection.basic;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouseX = x;
	mouseY = y;
	swarm.mouseVec = ofVec2f((float)(x)/ofGetWidth(),(float)(ofGetHeight()-y)/ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
