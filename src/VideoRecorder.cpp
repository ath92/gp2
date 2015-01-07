#include "VideoRecorder.h"


int i=0;  

void VideoRecorder::setup(){
	pixels.allocate(ofGetWidth(), ofGetHeight(), 4);
	counter  = 0;
	recording = false;
}

void VideoRecorder::beforeDraw(){
	//fbo.begin();  
	//draw now
}

void VideoRecorder::afterDraw(){
	//draw...  
	/*
	fbo.end();  

	fbo.readToPixels(pixels);  
	frames.push(ofBuffer()); 

	ofSaveImage(pixels,frames.back(),OF_IMAGE_FORMAT_JPEG); 
	fbo.draw(0,0);

	*/
	if(recording){
		saveImage();
	}
}

void VideoRecorder::saveImages(){
	while(!images.empty()){  
		images.front().resize(800,480);
		images.front().saveImage("snapshot" + ofToString(10000+i) + ".jpg");   
		images.pop();  
		i++;  
	} 
	cout << i << " images saved." << endl;
}


void VideoRecorder::saveImage(){
	ofImage img;
	img.grabScreen(0,0,ofGetWidth(), ofGetHeight());
	images.push(img);
	counter++;
	if(counter > 100){//prevent memory from accumulating too much
		saveImages();
		counter=0;
	}
	//img.saveImage("snapshot" + ofToString(10000+counter) + ".jpg");
}