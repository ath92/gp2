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
    gui->addSlider("zMultiplier", 0.0, 2, &s->zMultiplier);

	gui->addSpacer();
    gui->addSlider("damping", 0.00005, 0.00050, &s->damping);

	gui->addSpacer();
    gui->addSlider("forceStrength", 0, 2, &s->forceStrength);

	gui->addSpacer();
    gui->addSlider("influence", 0, 10, &s->influence);




	gui->addSpacer();
	
	gui->addSpacer();
	gui->addLabel("AESTHETIC VARIABLES");

	gui->addSpacer();
    gui->addSlider("opacity", 0.0, 1, &s->opacity);
	
	gui->addSpacer();
    gui->addSlider("opacityMultiplier", 1, 1000, &s->opacityMultiplier);

	gui->addSpacer();
    gui->addSlider("redMultiplier", 1, 100, &s->redMultiplier);

	gui->addSpacer();
    gui->addSlider("greenMultiplier", 1, 100, &s->greenMultiplier);

	gui->addSpacer();
    gui->addSlider("blueMultiplier", 1, 100, &s->blueMultiplier);
	
	gui->addSpacer();
    gui->addSlider("red", 0.0, 2, &s->red);

	gui->addSpacer();
    gui->addSlider("green", 0, 2, &s->green);

	gui->addSpacer();
    gui->addSlider("blue", 0, 2, &s->blue);

	
	

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