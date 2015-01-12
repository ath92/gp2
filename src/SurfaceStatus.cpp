//This serves as a universal status object for all surfaceflock states. In combination with ofxUI, it can be used to tweak, save and load settings.

#include "SurfaceStatus.h"

void SurfaceStatus::setup(WaveSurface * s){
	surface = s;
	//setup ui object
	gui = new ofxUISuperCanvas("Surface variables");
    gui->setPosition(212, 0);

	//initialize widgets
	gui->addSpacer();
	
	gui->addSpacer();
	gui->addLabel("BEHAVIORAL VARIABLES");

	gui->addSpacer();
    gui->addSlider("zMultiplier", 0.0, 2, &s->zMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("damping", 0.00005, 0.00050, &s->dampingTarget);

	gui->addSpacer();
    gui->addSlider("forceStrength", 0, 2, &s->forceStrengthTarget);

	gui->addSpacer();
    gui->addSlider("influence", 0, 10, &s->influenceTarget);




	gui->addSpacer();
	
	gui->addSpacer();
	gui->addLabel("AESTHETIC VARIABLES");

	gui->addSpacer();
    gui->addSlider("opacity", 0.0, 1, &s->opacityTarget);
	
	gui->addSpacer();
    gui->addSlider("opacityMultiplier", 1, 1000, &s->opacityMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("redMultiplier", 1, 100, &s->redMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("greenMultiplier", 1, 100, &s->greenMultiplierTarget);

	gui->addSpacer();
    gui->addSlider("blueMultiplier", 1, 100, &s->blueMultiplierTarget);
	
	gui->addSpacer();
    gui->addSlider("red", 0.0, 2, &s->redTarget);

	gui->addSpacer();
    gui->addSlider("green", 0, 2, &s->greenTarget);

	gui->addSpacer();
    gui->addSlider("blue", 0, 2, &s->blueTarget);

	
	

	gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&SurfaceStatus::guiEvent);

	//load xml
	load();
}

void SurfaceStatus::load(){
	//load xml
}

void SurfaceStatus::guiEvent(ofxUIEventArgs &e){
	//handle event
}

void SurfaceStatus::save(string name){
	//save xml
}