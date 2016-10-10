#include "ACC.h"

//--------------------------------------------------------------
void ACCClass::setup(){
    myserial.setup();
    ofSeedRandom(0);
    ofSetVerticalSync(true);
    
    iso.setup(10);
    iso.update();
    moveiso.setup(10);
    moveiso.update();
    
    signal1=false;
    signal2=false;
    signal3=false;
    signal4=false;
    signal5=false;
    
    ball1=0;
    ball2=0;
    ball3=0;
    ball4=0;
    ball5=0;
    
    
//    gui.setup();
//    gui.add(force.set("force", 0, 0, 0.001));
    
    force=0.005;
    
    ballPosition.set(0.55,0.55,0.55);
    

}

//--------------------------------------------------------------
void ACCClass::update(){
    myserial.update();
    vector<ofVec3f> ballmove;
    
    
    
    
    
//    for (int i=0; i<5; i++) {
//        ballmove.push_back(ofVec3f(ofNoise(ofGetElapsedTimef()/3+i/4),ofNoise(ofGetElapsedTimef()/2.5+(i+0.01)/4),ofNoise(ofGetElapsedTimef()/2+(i+0.2)/4)));
//    }

//    ballmove.push_back(ofVec3f(0.55,0.15,0.55));
    
    
    if (signal1==true) {
        ball1=ball1+0.001;
        
        }
    if (ball1>1) {
        ball1=0;
        signal1=false;
    }
    if (signal2==true) {
        ball2=ball2+0.001;
        
    }
    if (ball2>1) {
        ball2=0;
        signal2=false;
    }
    if (signal3==true) {
        ball3=ball3+0.001;
        
    }
    if (ball3>1) {
        ball3=0;
        signal3=false;
    }
    if (signal4==true) {
        ball4=ball4+0.001;
        
    }
    if (ball4>1) {
        ball4=0;
        signal4=false;
    }
    if (signal5==true) {
        ball5=ball5+0.001;
        
    }
    if (ball5>1) {
        ball5=0;
        signal5=false;
    }
    
    if (ballPosition.x<0.1) {
        ballPosition.x=0.1;
    }
    if (ballPosition.z<0.1) {
        ballPosition.z=0.1;
    }
    if (ballPosition.y<0.1) {
        ballPosition.y=0.1;
    }
    if (ballPosition.x>0.9) {
        ballPosition.x=0.9;
    }
    if (ballPosition.z>0.9) {
        ballPosition.z=0.9;
    }
    if (ballPosition.y>0.9) {
        ballPosition.y=0.9;
    }

    ballPosition.x += myserial.getDirection().x*force;
    ballPosition.z += myserial.getDirection().z*force;

    ballmove.push_back(ballPosition);
//    ballmove.push_back(ofVec3f(ofGetMouseX()*0.001,0.55,ofGetMouseY()*0.001));
    ballmove.push_back(ofVec3f(0.55,ball1,0.55));
    ballmove.push_back(ofVec3f(0.85,ball2,0.25));
    ballmove.push_back(ofVec3f(0.25,ball3,0.8));
    ballmove.push_back(ofVec3f(0.85,ball4,0.8));
    ballmove.push_back(ofVec3f(0.25,ball5,0.25));
//    cout<<ball1<<endl;

    
    iso.setCenters(ballmove);
    iso.setRadius(0.05,0.4);
    iso.update();
    
    
    ofMesh mesh1 = iso.getMesh();
    

    mesh1.save("out-ascii.ply", false);
    mesh1.save("out-binary.ply", true);

}

//--------------------------------------------------------------
void ACCClass::draw(){
    ofBackground(0);
    cam.begin();
    ofScale(800, 800, 800);
    iso.draw();
    myserial.draw();
    
    cam.end();
    myserial.drawDebug();
    
    gui.draw();

}

//--------------------------------------------------------------
void ACCClass::keyPressed(int key){
    if (key == '1'){
        signal1=true;
    }
    if (key == '2') {
        signal2=true;
    }
    if (key == '3') {
        signal3=true;
    }
    if (key == '4') {
        signal4=true;
    }
    if (key == '5') {
        signal5=true;
    }

}

