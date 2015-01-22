#pragma once

#include "ofMain.h"
#include "Person.h"
#include "WaveSurface.h"
#include "FlockStatus.h"
#include "SurfaceStatus.h"


const int characteristicTime = 120;


//thresholds between states

//Playground in smartxp

const float energyThreshold = 50;
const float proximityThreshold = 260;
const float chaosThreshold = 200;
const float multiEnergyThreshold = 25;

const float chaosDamping = 0.95;
/**/

//playground in designlab
/*
const float energyThreshold = 24;
const float proximityThreshold = 260;
const float chaosThreshold = 150;
const float multiEnergyThreshold = 20;

const float chaosDamping = 0.95;
/**/
//misc vars
const int numberOfStates = 6;
const string states[numberOfStates] = {"Energetic", "Chaotic", "Cold", "Calm", "Organized", "Warm"};

class People {

	public:
		Person * addPerson();
		void setup(WaveSurface * ws, FlockStatus * flockStatus, SurfaceStatus * surfaceStatus);
		void beforeUpdate();
		void update();
		void draw();
		void removePerson(Person * p);
		void movePerson(Person * p);
		void clear();
		void removeNotUpdated();

		Person * findByID(int id);

		list<Person *> people;
		WaveSurface * ws;

		FlockStatus * fs;
		SurfaceStatus * ss;

		//Behavior

		float energy;//average of energy of all people on the floor
		float proximity;//average distance of position vectors
		float chaos;//average distance of velocity vectors

		int counter;


		//states
		bool energeticCalm;
		bool organizedChaotic;
		bool warmCold;


		void updateBehavior();
		void updateState();

		int currentState;
};