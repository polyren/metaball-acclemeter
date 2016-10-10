#include "serial.hpp"

void serial::setup(){
    quat.set(0,0,0,1);
    port.setup("/dev/tty.usbmodem1411",9600);
    port.writeByte('r');
    aligned = 0;
    serialCount = 0;
}
ofVec3f serial::getDirection(){
    ofVec3f dir(1,0);
    
    return dir*quat;


}
void serial::draw(){
 
    
    ofPushStyle();
    ofVec3f dir(1,0,0);
    
    dir = dir*quat;
    
//    ofSetLineWidth(4);
//    ofSetColor(ofColor::orange);
//    ofDrawArrow(ofPoint(0.55,0.55,0.55), ofPoint(0.55,0.55,0.55) + dir*0.5 );
    ofPopStyle();

}
void serial::drawDebug(){
    
    string msg = "Aligned: "+ ofToString(aligned) + "\n";

    msg += "Interval: "+ ofToString(interval) + "\n";
    msg += "serialCount: "+ ofToString(serialCount) + "\n";
    msg += "teapotPacket: ";
    for (int i = 0; i < 14; i++) {
        msg += ofToString((int)teapotPacket[i]) + ", ";
    }
    
    
    ofDrawBitmapStringHighlight(msg, 100, 100);
    
}


void serial::update(){
    if(ofGetElapsedTimeMillis()-interval>10000){
        port.writeByte('r');
        interval=ofGetElapsedTimeMillis();
        cout << "port.writeByte('r');"<< endl;
    }
    if (port.available()) {
        interval=ofGetElapsedTimeMillis();// make this only happen when there is new serial data
    }
    while (port.available()) {
        int s = port.readByte();
        if((unsigned char) s == '\n' ){
            
            vector<string> numbers = ofSplitString(serialMsg, "\t");
//            sensorNumbers.clear();
            if (numbers.size() >= 4) {
                
                quat.set(ofToFloat(numbers[1]),ofToFloat(numbers[2]),ofToFloat(numbers[3]),ofToFloat(numbers[0]) );

            }
//            a = ofToInt(serialMsg);
            serialMsg = "";
        }else{
            serialMsg +=(unsigned char)s;
        }
        //cout<<(unsigned char)s;
        
    }
/*
    while (port.available() > 0) {
        int ch = port.readByte();
        cout << (unsigned char)ch;
        if(aligned<4){
            if (serialCount == 0) {
                if (ch == '$') aligned++; else aligned = 0;
            } else if (serialCount == 1) {
                if (ch == 2) aligned++; else aligned = 0;
            } else if (serialCount == 12) {
                if (ch == '\r') aligned++; else aligned = 0;
            } else if (serialCount == 13) {
                if (ch == '\n') aligned++; else aligned = 0;
            }
//            println(ch + " " + aligned + " " + serialCount);
            serialCount++;
            if (serialCount == 14) serialCount = 0;
        } else {
            if (serialCount > 0 || ch == '$') {
                teapotPacket[serialCount++] = (char)ch;
                if (serialCount == 14) {
                    serialCount = 0; // restart packet byte position
                    
                    // get quaternion from data packet
                    q[0] = ((teapotPacket[2] << 8) | teapotPacket[3]) / 16384.0f;
                    q[1] = ((teapotPacket[4] << 8) | teapotPacket[5]) / 16384.0f;
                    q[2] = ((teapotPacket[6] << 8) | teapotPacket[7]) / 16384.0f;
                    q[3] = ((teapotPacket[8] << 8) | teapotPacket[9]) / 16384.0f;
                    for (int i = 0; i < 4; i++) if (q[i] >= 2) q[i] = -4 + q[i];
                    
                    // set our toxilibs quaternion to new data
                    quat.set( q[1], q[2], q[3], q[0]);
                    cout<<quat[0]<< ", "<<quat[1]<< ", "<<quat[2]<< ", "<<quat[3]<<endl;//set this here because the line above updated quat
                }
            }
        }
    }//*/
}
