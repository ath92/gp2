#pragma once

#include "ofMain.h"



class VideoRecorder{

	public:
		void setup();
		void beforeDraw();
		void afterDraw();
		void saveImages();
		void saveImage();
		
		ofPixels pixels;  
		ofFbo fbo;
		queue<ofBuffer> frames;  
		queue<ofImage> images;  

		int counter;

		bool recording;

};
