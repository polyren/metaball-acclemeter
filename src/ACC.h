#pragma once

#include "ofMain.h"
#include "ofxMetaballs.h"
#include "serial.hpp"
#include "ofxGui.h"


class ACCClass : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    MarchingCubes iso;
    MarchingCubes moveiso;
    ofEasyCam cam;
    serial myserial;
    
    
    ofxPanel gui;
    
//    ofParameter<float> force;
    float force;
    float force1,force2,force3,force4,force5,force6;
    ofPoint ballPosition;
    
    float ball1,ball2,ball3,ball4,ball5;
    bool signal1,signal2,signal3,signal4,signal5;
		
};
