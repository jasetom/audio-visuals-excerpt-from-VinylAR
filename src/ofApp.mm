#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAntiAliasing();
    ofEnableSmoothing();

    ////Sound setup
    musicMan.setup();
        
    ////Visuals setup
    vizMan.setup();

    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(playy){
    vizMan.update(playy, ofGetScreenWidth()/2, ofGetScreenHeight()/2, 10, 10);
    
    
    vizMan.setRMS(musicMan.getRms());
    vizMan.setSpecFlatness(musicMan.getSpecFlatness());
    vizMan.setSpecCentroid(musicMan.getSpecCentroid1());
    vizMan.setPeakFreq(musicMan.getPeakFreq());
    vizMan.setIsBeat(musicMan.getIsBeatDetected());
    
    vizMan.setFFT(*musicMan.getFFT());
    vizMan.setMFCC(*musicMan.getMFCC());
    vizMan.setFFTOcatveAnalyzer(*musicMan.getFFTOctaveAnalyzer());
    
//    //fft size/2
//    for(int i=0; i < musicMan.getFftSize() / 2; i++) {
//        vizMan.setFFTmagnitudes(musicMan.getFftMagnitudes(i));
//    }
//    
//    //13 mffcs
//    for(int i=0; i < 13; i++) {
//        vizMan.setMFFCs(musicMan.getMfccs(i));
//    }
//    
//    for(int i=0; i < musicMan.getOctaveAvgN(); i++) {
//        vizMan.setOctaveAverages(musicMan.getOctaveAvg(i));
//    }
//    
//    //devide pitches into 12
//    for(int i=0; i < 12; i++) {
//        vizMan.setPitchHistogram(musicMan.getPitchHistogram(i));
//    }
//    
//    //42 mel bands
//    for(int i=0; i < 42; i++) {
//        vizMan.setMelBands(musicMan.getMelBands(i));
//    }

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor(0,146,146),ofColor(0,200),OF_GRADIENT_CIRCULAR);
    
//    ofBackground(0,146,146);
//    ofPushMatrix();
    ofSetColor(255);
    vizMan.drawFbo();
    ofSetColor(255);
//    ofPopMatrix();

	
}


//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    //audio output comming from music manager class.
    musicMan.audioOut(output,bufferSize,nChannels);
    playy = true;
    
}






//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
