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
	gui->addSlider("speed", 0.1, 2, &s->speedTarget);
	
	gui->addSpacer();
	gui->addSlider("repelStrength", 5, 50, &s->repelStrengthTarget);

	gui->addSpacer();
    gui->addSlider("influence", 0.005, 0.1, &s->influenceTarget);
	
	gui->addSpacer();
    gui->addSlider("mouseInfluence", 0.001, 0.01, &s->mouseInfluenceTarget);
	
	gui->addSpacer();
	gui->addSlider("maxSpeed", 0.005, 0.050, &s->maxSpeedTarget);
	
	gui->addSpacer();
    gui->addSlider("randomness", 0.0005, 0.001, &s->randomnessTarget);
	
	gui->addSpacer();
	gui->addSlider("separationDistance", 0.1, 1, &s->separationDistanceTarget);
	
	gui->addSpacer();
	gui->addSlider("neighborDistance", 0.5, 5, &s->neighborDistanceTarget);
	
	
	gui->addSpacer();
	gui->addLabel("AESTHETIC VARIABLES");

	gui->addSpacer();
    gui->addIntSlider("drawSize", 10, 100, &s->drawSizeTarget);

	gui->addSpacer();
    gui->addSlider("brightness", 0.1, 1, &s->brightnessTarget);

	gui->addSpacer();
    gui->addSlider("opacity", 0.1, 1, &s->opacityTarget);

	gui->addSpacer();
    gui->addSlider("redMultiplier", 1, 100, &s->redMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("greenMultiplier", 1, 100, &s->greenMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("blueMultiplier", 1, 100, &s->blueMultiplierTarget);

	
	gui->addSpacer();
    gui->addSlider("red", 0.0, 1, &s->redTarget);

	gui->addSpacer();
    gui->addSlider("green", 0, 1, &s->greenTarget);

	gui->addSpacer();
    gui->addSlider("blue", 0, 1, &s->blueTarget);

	



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