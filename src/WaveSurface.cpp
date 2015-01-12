#include "ofApp.h"
#include "WaveSurface.h"
#include <math.h>
//--------------------------------------------------------------

bool moveWave = true;

void WaveSurface::setup()
{
	//set behvioral variables
	zMultiplier = 2;
	damping = 0.0001;
	forceStrength = 1;
	influence = 3;
	random = 0;

	//set aesthetic variables
	opacity = 1;
	opacityMultiplier = 1.0;
	redMultiplier = 1.0;
	greenMultiplier = 1.0;
	blueMultiplier = 1.0;
	red = 1.0;
	green = 0.1;
	blue = 0.1;
	colorBrightness = 100;
	drawLines = false;

	derivativeTexture.allocate(width,height,GL_RGBA);
	derivativePixels.allocate(width,height,OF_PIXELS_RGB);


	scale = ofVec2f(ofGetWidth()/width, ofGetHeight()/height);
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			mesh.addVertex(ofPoint(x*scale.x-width*(scale.x/2) +ofRandom(random) ,y*scale.y-height*(scale.y/2) + ofRandom(random) ,0)); 
			mesh.addTexCoord(ofPoint(x*50, y*50));
			mesh.addColor(ofFloatColor(0,0,0));  
			grid[y*width+x] = 0;
			deltagrid[y*width+x] = 0;
			offset[y*width+x] = ofRandom(random);
		}
	}
 
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){

			//indices plaatsen zodat triangles gevormd worden
			mesh.addIndex(x+y*width);              
			mesh.addIndex((x+1)+y*width);          
			mesh.addIndex(x+(y+1)*width);           
 
			mesh.addIndex((x+1)+y*width);           
			mesh.addIndex((x+1)+(y+1)*width);       
			mesh.addIndex(x+(y+1)*width);           
		}
	}
	staystill = false;

	//plaatje
	ofLoadImage(tex, "images/outer_space.jpg");
}

void WaveSurface::update(){

	float currentgrid[width*height];
	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			//copy the grid before changing it 
			currentgrid[y*width+x] = grid[y*width+x];
			//modify the grid based on the changes of other parts of the grid
			grid[y*width+x] += avgDelta(x,y);

			//add some damping
			grid[y*width+x] = grid[y*width+x] * (1-damping);

			//color it up
			float col = 0;

			float thisValue, previousValue;
			if(x>0){
				thisValue = grid[y*width+x] + offset[y*width+x];
				previousValue = grid[y*width+x-1] + offset[y*width+x-1];
				derivativex[x+y*width] = previousValue - thisValue;
				col = (derivativex[x+y*width]*-1+30)/(800-colorBrightness);
				//derivativex[x+y*width] = derivativex[x+y*width] < 0 ? -sqrt(abs(derivativex[x+y*width])) : sqrt(derivativex[x+y*width]);//take square root
				derivativex[x+y*width] = derivativex[x+y*width]<0? -derivativex[x+y*width] * derivativex[x+y*width]/1000 : derivativex[x+y*width] * derivativex[x+y*width]/1000;//square
			}
			if(y>0){
				thisValue = grid[y*width+x] + offset[y*width+x];
				previousValue = grid[(y-1)*width+x] + offset[(y-1)*width+x];
				derivativey[x+y*width] = previousValue - thisValue;
				//derivativey[x+y*width] = derivativey[x+y*width] < 0 ? -sqrt(abs(derivativey[x+y*width])) : sqrt(derivativey[x+y*width]);//take square root
				derivativey[x+y*width] = derivativey[x+y*width]<0?-derivativey[x+y*width]*derivativey[x+y*width]/1000:derivativey[x+y*width]*derivativey[x+y*width]/1000;//square
			}
			//Dampen out the minor things that happen sometimes.
			//if(derivativex[x+y*width] < 50 && derivativex[x+y*width] > -50) derivativex[x+y*width] = 0;
			//if(derivativey[x+y*width] < 50 && derivativey[x+y*width] > -50) derivativey[x+y*width] = 0; 

			derivativePixels.setColor(x,y,ofFloatColor(derivativex[x+y*width]/80 + 0.5, derivativey[x+y*width]/80 + 0.5, 0));
			mesh.setColor(y*width+x, ofFloatColor(col*redMultiplier*red + .3,col*greenMultiplier*green + .3,col*blueMultiplier*blue + .3,opacity*opacityMultiplier));
			//mesh.setColor(y*width+x, ofFloatColor(1,1,1));

			//update the mesh
			ofVec3f vert = mesh.getVertex(y*width+x);
			float z = sqrt(abs(grid[y*width+x]))*2;
			z *= 2;
			z=0;
			vert.z = grid[y*width+x] > 0 ? z : -z;
			vert.z += 100;//zoom
			vert.z += offset[y*width+x];
			mesh.setVertex(x+width*y,vert);
		}
	}

	smoothDerivative(10);
	derivativeTexture.loadData(derivativePixels);
	for(int i = 0; i < width*height;i++){
		deltagrid[i] = grid[i]-currentgrid[i];
	}
}


void WaveSurface::draw(){
	if(staystill)cam.reset();
	//mesh.drawWireframe();
	ofSetColor(ofColor(0,0,0,.2));
	ofRect(0,0,ofGetWidth(), ofGetHeight());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	tex.bind();
	mesh.draw();


	ofSetColor(255,0,255);
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			if(drawLines) ofLine(x*scale.x - width*scale.x/2 , y*scale.y - height*scale.y/2 , x*scale.x+derivativex[x+y*width]/10  - width*scale.x/2 ,y*scale.y+derivativey[x+y*width]/10  - height*scale.y/2);
		}
	}
	ofSetColor(255);
	//derivativeTexture.draw(-ofGetWidth()/6,-ofGetHeight()/6,ofGetWidth()/3,ofGetHeight()/3);
}

float WaveSurface::avgDelta(int x, int y){
	float total = 3*deltagrid[y*width+x];//Switch x and y to add symmetry!
	total -= grid[y*width+x]*.2;
	int counter=3;
	if(x>0){
		total+=deltagrid[y*width+(x-1)];
		counter++;
	}
	if(y>0){
		total+= deltagrid[(y-1)*width+x];
		counter++;
	}
	if(x<width-1){
		total+= deltagrid[y*width+x+1];
		counter++;
	}
	if(y<height-1){
		total+= deltagrid[(y+1)*width+x];
		counter++;
	}

	//Diagonal propagation
	/*
	if(x<width-1 && y<height-1){
		total+= deltagrid[(y+1)*width+x+1];
		counter++;
	}

	
	if(x>0 && y>0){
		total+=deltagrid[(y-1)*width+(x-1)];
		counter++;
	}

	if(x>0 && y<height-1){
		total+= deltagrid[(y+1)*width+x-1];
		counter++;
	}
	if(x<width-1 && y > 0){
		total+= deltagrid[(y-1)*width+x+1];
		counter++;
	}*/

	return total/counter;
}


void WaveSurface::applyForce(float x, float y){
	for(int ix = x-influence; ix < x+influence; ix++){
		for(int iy = y-influence; iy < y+influence; iy++){
			if(ix > 0 && ix < width*scale.x && iy > 0 && iy < height*scale.y){
				float distance = 1.5-(abs(ix-x) * abs(iy-y))/(influence*influence);
				int pos = (ix/(int)scale.x)+(((int)ofGetHeight()-iy)/(int)scale.y)*width;
				deltagrid[pos] += forceStrength*distance*10*((float)width/50);
			}
		}
	}
}


void WaveSurface::applySuddenForce(float x, float y){
	for(int ix = x-influence; ix < x+influence; ix++){
		for(int iy = y-influence; iy < y+influence; iy++){
			if(ix > 0 && ix < width*scale.x && iy > 0 && iy < height*scale.y){
				float distance = 1.5-(abs(ix-x) * abs(iy-y))/(influence*1);
				int pos = (ix/(int)scale.x)+(((height*(int)scale.y)-iy)/(int)scale.y)*width;
				deltagrid[pos] += forceStrength*distance*10;
			}
		}
	}
}

void WaveSurface::releaseSuddenForce(float x, float y){
	for(int ix = x-influence; ix < x+influence; ix++){
		for(int iy = y-influence; iy < y+influence; iy++){
			if(ix > 0 && ix < width*scale.x && iy > 0 && iy < height*scale.y){
				float distance = 1.5-(abs(ix-x) * abs(iy-y))/(influence*1);
				int pos = (ix/(int)scale.x)+(((height*(int)scale.y)-iy)/(int)scale.y)*width;
				deltagrid[pos] -= forceStrength*distance*10;
			}
		}
	}
}

void WaveSurface::smoothDerivative(int smooth){
	float copyx[width*height];
	copy(begin(derivativex), end(derivativex), begin(copyx));
	float copyy[width*height];
	copy(begin(derivativey), end(derivativey), begin(copyy));

	//calculate total weight of neighbors
	float smoothWeight = 0;
	for(int i = 1; i<smooth; i++){
		smoothWeight += 1/i*2;
	}


	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			ofVec2f total = ofVec2f(0,0);
			for(int ix = x-smooth; ix < x+smooth; ix++){
				for(int iy = y-smooth; iy < y+smooth; iy++){
					if(ix > 0 && ix < width && iy > 0 && iy < height && !(ix==x&&iy==y)){
						total += ofVec2f(copyx[iy*width+ix], copyy[iy*width+ix]) * (1/((float)abs(x-ix)+1)) * (1/((float)abs(y-iy)+1));
					}
				}
			}
			derivativex[y*width+x] = derivativex[y*width+x] * 0.5 + (total.x/smoothWeight) * 0.5;
			derivativey[y*width+x] = derivativey[y*width+x] * 0.5 + (total.y/smoothWeight) * 0.5;
		}
	}
}