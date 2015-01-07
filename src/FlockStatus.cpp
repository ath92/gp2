//This serves as a universal status object for all surfaceflock states. In combination with ofxUI, it can be used to tweak, save and load settings.

#include "FlockStatus.h"

void FlockStatus::setup(Swarm * s){
	swarm = s;
	//setup ui object
	gui = new ofxUISuperCanvas("Swarm variables");

	//initialize widgets
	gui->addSpacer();
	gui->addSpacer();
	gui->addSpacer();
	gui->addLabel("BEHAVIORAL VARIABLES");
	
	gui->addSpacer();
	gui->addSlider("speed", 0.1, 2, &s->speed);
	
	gui->addSpacer();
	gui->addSlider("repelStrength", 5, 50, &s->repelStrength);

	gui->addSpacer();
    gui->addSlider("influence", 0.005, 0.1, &s->influence);
	
	gui->addSpacer();
    gui->addSlider("mouseInfluence", 0.001, 0.01, &s->mouseInfluence);
	
	gui->addSpacer();
	gui->addSlider("maxSpeed", 0.005, 0.050, &s->maxSpeed);
	
	gui->addSpacer();
    gui->addSlider("randomness", 0.0005, 0.001, &s->randomness);
	
	gui->addSpacer();
	gui->addSlider("separationDistance", 0.1, 1, &s->separationDistance);
	
	gui->addSpacer();
	gui->addSlider("neighborDistance", 0.5, 5, &s->neighborDistance);
	
	
	gui->addSpacer();
	gui->addLabel("AESTHETIC VARIABLES");

	gui->addSpacer();
    gui->addIntSlider("drawSize", 10, 100, &s->drawSize);

	gui->addSpacer();
    gui->addSlider("brightness", 0.1, 1, &s->brightness);

	gui->addSpacer();
    gui->addSlider("opacity", 0.1, 1, &s->opacity);

	gui->addSpacer();
    gui->addSlider("redMultiplier", 1, 100, &s->redMultiplier);

	gui->addSpacer();
    gui->addSlider("greenMultiplier", 1, 100, &s->greenMultiplier);

	gui->addSpacer();
    gui->addSlider("blueMultiplier", 1, 100, &s->blueMultiplier);

	
	gui->addSpacer();
    gui->addSlider("red", 0.0, 1, &s->red);

	gui->addSpacer();
    gui->addSlider("green", 0, 1, &s->green);

	gui->addSpacer();
    gui->addSlider("blue", 0, 1, &s->blue);

	



	gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&FlockStatus::guiEvent);

	//load xml
	load();
}

void FlockStatus::load(){
	//load xml
}

void FlockStatus::guiEvent(ofxUIEventArgs &e){
	//handle event
	string n = e.getName();
	if(n=="brightness"||n=="opacity"||n=="redMultiplier"||n=="greenMultiplier"||n=="blueMultiplier"||n=="red"||n=="green"||n=="blue"){
		swarm->setColors();
	}
}

void FlockStatus::save(string name){
	//save xml
}