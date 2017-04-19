#pragma once

#include "ofxiOS.h"
#include "VisualsManager.hpp"
#include "MusicManager.hpp"

class ofApp : public ofxiOSApp {
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
    MusicManager musicMan;
    VisualsManager vizMan;
    
    bool playy;
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
    

};


