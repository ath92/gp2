#version 120
#extension GL_ARB_texture_rectangle : enable
#define KERNEL_SIZE 9

uniform sampler2DRect backbuffer;// recive the previous velocity texture
uniform sampler2DRect posData;// recive the position texture
uniform sampler2DRect waveSurface;// recive the position texture

uniform int   posWidth;
uniform int   posHeight;

uniform float   surfaceWidth;
uniform float   surfaceHeight;

// flocking parameters
uniform float separationDistance;
uniform float neighborDistance;
uniform float crowdDistance;

//mouse
uniform float mouseX;
uniform float mouseY;
vec2 mouseVec;

uniform float influence;
uniform float wallDistance;
uniform float wallInnfluence;
uniform float mouseInfluence;
uniform float repelStrength;
uniform float maxSpeed;
uniform float randomness;


float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 flock(vec3 p, vec3 v){
    vec3 oldv = v;

    float neighborCounter = 0;
    //p=positon, v=velocity of current boid

    for ( int x =0; x < posWidth; x ++){
        for (int y=0; y < posHeight; y++) {

            //Position and velocity of other boid
            vec3 pos = texture2DRect( posData, vec2(x,y)).xyz;
            vec3 vel = texture2DRect( backbuffer, vec2(x,y) ).xyz;


            float dif =  distance (pos, p);

            //Check if we should attract or repel

            if(dif < crowdDistance){
                neighborCounter+=1;
                if(dif>separationDistance/posWidth && dif < neighborDistance/posWidth){//attract
                    v = v * (1-influence) + vel * influence;
                } else if(dif<separationDistance/posWidth){//repel
                    v += (p - pos) * influence * repelStrength;
                }
            }
        }
    }

	


	
    if(p.x < 0.005) v.x += 0.005;
    if(p.y < 0.005) v.y += 0.005;
    if(p.x > (1-0.005)) v.x -= 0.005;
    if(p.y > (1-0.005)) v.y -= 0.005;
	


    //move towards mouse
    //if(distance(vec2(p.x,p.y),mouseVec) < mouseInfluence*60) v += (p - vec3(mouseVec.x,mouseVec.y,0)) * mouseInfluence;

    //move toward center, slowly
    v.x -= (p.x - 0.5) * 0.0002;
    v.y -= (p.y - 0.5) * 0.0002;

    //random?
    v -= v * rand(vec2(v.x,v.y)) * randomness * (neighborCounter/10000);


	//tendency to go down
	v.z -= p.z*0.00015;

	//but not too high
	if(p.z > 0.195) v.z -= (p.z-0.195)/20;
	if(p.z < 0.005) v.z += 0.005;

    if(length(v) > maxSpeed){
        v *= 0.8;
    }

    if(length(v)  < maxSpeed/10){
        v *= 1.2;
    }

	//wave surface
	
    vec3 wsVec = texture2DRect( waveSurface, vec2(int(p.x*surfaceWidth+0.5),int(p.y*surfaceHeight+0.5))).xyz;//20=surface resolution. +0.5 to round by casting to int
	v.x += (wsVec.x-0.498)*0.02;//0.498 because there seems to be some sort of rounding error. This fixes it (hacky)
	v.y += (wsVec.y-0.498)*0.02;

    return v;
}


void main(void){

    mouseVec.x = mouseX;
    mouseVec.y = mouseY;
    vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...
    
    vec3 pos = texture2DRect( posData, st).xyz;      // ... for getting the position data
    vec3 vel = texture2DRect( backbuffer, st ).xyz;  // and the velocity
    
    // Calculates what´s going to be the next position without updating it.
    // Just to see if it collide with the borders of the FBO texture
    //
    vel = flock(pos, vel);
    
    gl_FragColor = vec4(vel.x,vel.y,vel.z,1.0);   // Then save the vel data into the velocity FBO
}
