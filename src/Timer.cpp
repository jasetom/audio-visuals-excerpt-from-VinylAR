//
//  Timer.cpp
//  viz_experiments
//
//  Created by Tomas on 18/04/2017.
//
//

#include "Timer.hpp"

//-----------------------------------------------------
void Timer::update(int type){
    
    //type 1 is for animations
    //type 2 is for shaders
    
    if (bTimerFinished) {
        
        bTimerFinished = false;

        timerStartTime = ofGetElapsedTimeMillis();
        if(type==1){
        timerEndTime = ofRandom(3000, 7000);
        }
    }
    
    int timer = ofGetElapsedTimeMillis() - timerStartTime;
    
    if(timer >= timerEndTime && !bTimerFinished) {
        bTimerFinished = true;
        if(type==2){
            timerEndTime = 1000;
        }

        
    }

    
    
}


//-----------------------------------------------------
bool Timer::isFinished(){
    return bTimerFinished;
}
