

#ifndef serial_hpp
#define serial_hpp

#include "ofMain.h"

class serial  {
    
public:
    
    void setup();
    void draw();
    void update();
    void drawDebug();
    ofSerial port;
    char teapotPacket[14];
    int serialCount = 0;
    int aligned=0;
    int interval=0;
    
    float q [4];
    ofQuaternion quat;// use the ofQuaternion class instead of ofVec4f
        string serialMsg;
    ofVec3f getDirection();
    
};

//your code should be before the line bellow

#endif /* serial_hpp */

