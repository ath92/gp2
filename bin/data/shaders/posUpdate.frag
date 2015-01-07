#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect prevPosData;  // recive the previus position texture
uniform sampler2DRect velData;      // recive the velocity texture

uniform float speed;

void main(void){
    vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...
    
    vec3 pos = texture2DRect( prevPosData, st ).xyz; // ... in order to look at a particulary place on it
    vec3 vel = texture2DRect( velData, st ).xyz;     // Fetch both the pos and vel.
    
    pos += vel*speed;
    
    // wrap
    if ( pos.x < 0.0)
        pos.x = 1.0;
    
    if ( pos.x > 1.0)
        pos.x = 0.0;
    
    if (pos.y < 0.0)
        pos.y = 1.0;
    
    if ( pos.y > 1.0)
        pos.y = 0.0;

    if (pos.z < 0.0)
        pos.z = 0.2;
    
    if ( pos.z > 0.3)
        pos.z = 0.0;
    
    gl_FragColor.rgba = vec4(pos.x,pos.y,pos.z,1.0);  // And finaly it store it on the position FBO
}