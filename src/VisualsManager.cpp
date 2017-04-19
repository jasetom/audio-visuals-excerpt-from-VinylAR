//
//  VisualsManager.cpp
//  VinylAR2
//
//  Created by Tomas on 05/04/2017.
//
//

#include "VisualsManager.hpp"
#include "ofxiOSPostGlitch.hpp"


//-----------------------------------------------------
void VisualsManager::setup(){
    
    setupShaders();
    setupManyBoxes();
    setupIcoSphere();
    setupCone();
    setupSmallCubes();
    setupSphereAndCones();
    setupCylinders();
    setupBoxesV3();

}

//----------------------------------------------------
void VisualsManager::setupShaders(){
    
    //glitch
    myFbo.allocate(ofGetScreenWidth(), ofGetScreenHeight()); //this line is changed
    effectShaders.setupFBO(&myFbo);
    effectNumber = 0;
    
    
}

//-----------------------------------------------------
void VisualsManager::setupManyBoxes(){
    
    ofSetLineWidth(10);
    //    ofSetBackgroundAuto(false);
    
}

//-----------------------------------------------------
void VisualsManager::setupIcoSphere(){
    
    icoSphere.setRadius(10);
    
    material.setShininess(120);
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetIcoSphereResolution(24);
//    icoSphere.setResolution(25);
    
    icoSphereMode = 0;
    
    icoSphere2 = icoSphere;
    
}

//-----------------------------------------------------
void VisualsManager::setupCone(){
    
    cone.set(50, 50);
    
    coneMode = 0;
    
}

//-----------------------------------------------------
void VisualsManager::setupSmallCubes(){
    smallCubesSize = 70;
    
    cube.set(smallCubesSize);
    
    for(int i =0; i < 6; i ++){
        smallCubes.push_back(ofBoxPrimitive());
    }
    
    for(int i =0; i < smallCubes.size(); i++){
        smallCubes[i].setParent(cube);
        smallCubes[i].set(smallCubesSize/3);
    }
}

//-----------------------------------------------------
void VisualsManager::setupSphereAndCones(){
    
    sphere.set(100,20);
    sphere.setResolution(0);
    
    for(int i=0;i<10;i++){
        cones.push_back(ofConePrimitive());
        cones2.push_back(ofConePrimitive());

    }
    
    for(int i=0;i<cones.size();i++){
        cones[i].set(36, 100);
        cones[i].setParent(sphere);
        cones2[i].set(36, 100);
        cones2[i].rotate(180, 180, 1, 1);
        cones2[i].setParent(sphere);
    }
}

//-----------------------------------------------------
void VisualsManager::setupCylinders(){
    
    for(int i = 0; i < 36; i++){
        cylinders.push_back(ofCylinderPrimitive());
    }
    
}

//-----------------------------------------------------
void VisualsManager::setupBoxesV3(){
    
    boxV3.set(10);
    
    //boxes
    for(int i = 0; i < 5; i++){
        boxesV3.push_back(ofBoxPrimitive());
        boxesV3[i].setResolution(1);
        
    }
    
    for(int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++){
        boxSidesV3[i] = boxV3.getSideMesh(i);
    }
    
    for(int i = 0; i < boxesV3.size(); i++ ){
        for(int j = 0; j < ofBoxPrimitive::SIDES_TOTAL; j++){
            boxesSidesV3[i].push_back(boxesV3[i].getSideMesh(j));
        }
    }

    
    
}



//--- End of setup
//-----------------------------------------------------
//--- Update function

//-----------------------------------------------------
void VisualsManager::update(bool isPlaying, int posX, int posY, int posZ, int scale){
    
    switchTimer.update(1);
    shadersTimer.update(2);
    
    ///everything we put in here will be affected by effect shaders
    myFbo.begin();
    ofClear(0,0,0,0);
    //scale shall be added
    if(isPlaying==true){
        
        draw(posX, posY, posZ, scale);
    }
    
    myFbo.end();
    
    effectShaders.update(&myFbo);
    
}

//--- End of update
//-----------------------------------------------------
//--- Draw functions


//-----------------------------------------------------
void VisualsManager::draw(int posX, int posY, int posZ, int scale){
    globalPosX = posX;
    globalPosY = posY;
    globalPosZ = posZ;
    globalScale = scale;
    
    ofSetColor(255);
    
//    cout << "rms: " << RMS;
//    cout << ", spFlat: " << specFlatness;
//    cout << ", spCentr: " << specCentroid;
//    cout << ", pkFrq: "  << peakFreq;
//    cout << ", isBeat: "  << isBeat <<endl;

//    if(specCentroid>0.1){
//        for(int i=0; i < 42; i++) {
//            cout << mfcc->melBands[i] << ",";
//        }
//     }
    if(specCentroid>0.1){
        float avg;

    for(int i=0; i < octaves->nAverages; i++) {
        avg += octaves->averages[i];
        cout<<"octave averages i: " << avg << endl;
        
        //setting up threshold values for octave averages
        
        clrScheme0=false;
        clrScheme1=false;
        clrScheme2=false;
        clrScheme3=false;
        clrScheme4=false;
        clrScheme5=false;

        
        if(avg<450){
            clrScheme0=true;
        }else if(avg>450 && avg<550){
            clrScheme1=true;
        }else if (avg>550 && avg<650){
            clrScheme2=true;
        }else if(avg>650 && avg<750){
            clrScheme3=true;
        }else if(avg>7500 && avg<850){
            clrScheme4=true;
        }else if(avg>850){
            clrScheme5=true;
        }
        
    }
//
//        
//
//
//        
//        cout<< "bAvg0: " << bAvg0;
//        cout<< " bAvg1: " << bAvg1;
//        cout<< " bAvg2: " << bAvg2;
//        cout<< " bAvg3: " << bAvg3;
//        cout<< " bAvg4: " << bAvg4;
//        cout<< " bAvg5: " << bAvg5 << endl;
//
        
    
    }
    
    
    if(specCentroid>0.1){
        
        for(int i=0; i < 13; i++) {
//            cout<<"mffcs melbands[i]: " << mfcc->melBands[i] << endl;
        }
        
    }
    
    
    ////shaders
    int shaderNo = 0;//ofRandom(0, 8);
    //shaderno 0 = colour split
    //shaderno 1 = soft shakyness, blurs out sides
    //shaderno 2 = shakes the screen slightly
    //shaderno 3 = chaotic wiggle, twists and turns
    //shaderno 4 = blurry squares, moving in blocks
    //shaderno 5 = produces slight wavey effect, does not distort
    //shaderno 6 = changes colours, seems like an inverse


    if(isBeat){
        effectShaders.setShaderOn(shaderNo);
    }else{
        effectShaders.setShaderOff(shaderNo);
    }
    

    
    if(switchTimer.isFinished()){
    
        effectShaders.setShaderOn(0);
        effectShaders.setShaderOn(5);
        effectShaders.setShaderOn(2);

        vizNum = ofRandom(0,7);
    }
    
    if(shadersTimer.isFinished()){
        effectShaders.setShaderOff(0);
        effectShaders.setShaderOff(5);
        effectShaders.setShaderOff(2);
    }

    
    switch(vizNum){
        case 0:
            ///0 cone with normals sticking out
            for(int i=0; i< 20; i++){
                if(peakFreq>300){
                    drawCone(0,fft->magnitudes[i],specCentroid,1.0);
                }else{
                    drawCone(1,100,specCentroid,1+RMS);
                }
            }
            break;
            
        case 1:
            ///1 cube with small cubes on sides
            drawSmallCubes(RMS, peakFreq/50);
            break;
            
        case 2:
            ////2 many boxes turning into balls
            if(specCentroid>0.5){
//                ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
                drawManyBoxes(specCentroid,200.0,300.0,1);
            }else{
                ofSetColor(0, 130, 250);
                drawManyBoxes(specCentroid,peakFreq,300.0,0);
            }
            break;
            
        case 3:
            ////3 exploded sphere
            for(int i=0; i< 20; i++){
                if(specCentroid>0.4){
                    drawIcoSphere(0,RMS*100,fft->magnitudes[i]);
                }else{
                    drawIcoSphere(1,specCentroid,peakFreq/100);
            
                }
            }
            break;
            
        case 4:
            ////4 circle + cones around
            if(specCentroid>0.1){
                drawSphereAndCones(peakFreq/100, specCentroid, RMS);
            }else if(specCentroid>0.3){
                drawSphereAndCones(peakFreq/100, specCentroid, specFlatness);
            }
            break;
            
        case 5:
            ////5 cylinders
            if(specCentroid>0.01){
                drawCylinders(RMS, specCentroid,isBeat);
            }
            break;
            
        case 6:
            ////6 splitup boxes
            if(specCentroid>0.01){
                drawBoxesV3(RMS, specCentroid);
                rndmNum = ofRandom(0, 2);
            }else if(isBeat){
                rndmNum = ofRandom(0, 7);
            }else if(specFlatness>0.07){
                rndmNum = ofRandom(0, 1);
            }
            break;
    }


    
    }


//-----------------------------------------------------
void VisualsManager::drawFbo(){
    effectShaders.draw(0,0);
}


//-----------------------------------------------------
void VisualsManager::drawManyBoxes(float param1, float param2, float param3, int boxStyle){

    //boxesv2
    
    //    float cloudSize = param1/2.0;
    float cloudSize = ofGetWidth()/2;
    
    float maxBoxSize = 50;//original 50
    //    float maxBoxSize = mouseY/100.0;
    
    float spacing = 10; //origial 1
    int boxCount = param2/10; //original 100
    
    ofTranslate(globalPosX,globalPosY);
    
    for(int i = 0; i < boxCount; i++) {
        ofPushMatrix();
        
        float t = (ofGetElapsedTimef() + param1 + i * spacing); //original
//        float t = (param1 + i * spacing);
        ofVec3f pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    ofSignedNoise(0, 0, t));
        
        float boxSize = maxBoxSize * ofSignedNoise(pos.x, pos.y, pos.z);
        
        pos *= cloudSize;
        ofTranslate(pos);
        ofRotateX(pos.x);
        ofRotateY(pos.y);
        ofRotateZ(pos.z);
        
        ofNoFill();
        
        
        
        if(clrScheme0){ //red
            ofSetColor(250-mfcc->melBands[(int)ofRandom(0,42)],0,100);
        }else if(clrScheme1){//orange
            ofSetColor(255-mfcc->melBands[(int)ofRandom(0,42)],69+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme2){//yellow
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme3){//green
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if (clrScheme4){//blue
            ofSetColor(75,0,255+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }else if(clrScheme5){//indigo
            ofSetColor(75,0,130+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }

        
        if(boxStyle==0){
            ofDrawSphere(boxSize * 1.1f);
        }else if(boxStyle==1){
            ofDrawBox(boxSize * 1.1f);
        }
        
        
        ofPopMatrix();
    }
    
    
    
}

//-----------------------------------------------------
void VisualsManager::drawIcoSphere(int icoSphereMode,float param1, float param2){
        
    icoSphere.setPosition(globalPosX, globalPosY,globalPosZ);
    icoSphere2.setPosition(globalPosX, globalPosY,globalPosZ);
    icoSphere.rotate(abs(param1/100), 1.0, 0.0, 0.0);
    
    if(icoSphereMode ==0){
        
        ofFill();
        triangles = icoSphere.getMesh().getUniqueFaces();
        float angl = (param2 * 1.4);
        ofVec3f faceNormal;
        for(size_t i = 0; i < triangles.size(); i++ ) {
            float frc = ofSignedNoise(angl* (float)i * .2, angl*.02) * 3;
            faceNormal = triangles[i].getFaceNormal();
            for(int j = 0; j < 3; j++ ) {
                ofSetColor(ofRandom(100,130), ofRandom(100,255), ofRandom(100,110));
                triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * frc );
            }
        }
        icoSphere.getMesh().setFromTriangles(triangles);
        icoSphere.drawFaces();

    }else if(icoSphereMode==1){
        ofSetColor(ofRandom(100,120), ofRandom(100,110),ofRandom(100,255));

        if(param1>0.2){
            
            icoSphere2.setScale(param2);
            icoSphere2.drawWireframe();
        }else{
            icoSphere2.setScale(param2);
            icoSphere2.draw();

        }
        icoSphere = icoSphere2;
    }
    
    
}

//-----------------------------------------------------

void VisualsManager::drawCone(int coneMode, float param1, float param2, float param3){
    
    cone.setPosition(globalPosX, globalPosY, globalPosZ);
    
    
    float angle = param2;
    
    
    cone.rotate(angle, 1.0, 0.0, 0.0);
    
//    if(coneMode == 1) {
//        bottomCap   = cone.getCapMesh();
//        body        = cone.getConeMesh();
//        
//        ofSetColor(255,0,0);
//        bottomCap.draw();
//        body.draw();
//    }
    
    if(coneMode==0){
        ofSetColor(255);
    }else if(coneMode==1){
        
        if(clrScheme0){ //red
            ofSetColor(250-mfcc->melBands[(int)ofRandom(0,42)],0,100);
        }else if(clrScheme1){//orange
            ofSetColor(255-mfcc->melBands[(int)ofRandom(0,42)],69+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme2){//yellow
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme3){//green
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if (clrScheme4){//blue
            ofSetColor(75,0,255+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }else if(clrScheme5){//indigo
            ofSetColor(75,0,130+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }
    }
        cone.drawNormals(param1, false);
        cone.setScale(param3+.01f);
    
        cone.drawWireframe();
        cone.setScale(param3-.1f);
        cone.draw();

}

//-----------------------------------------------------
void VisualsManager::drawSmallCubes(float param1, float param2){
    
    cube.setPosition(globalPosX,globalPosY,globalPosZ);
    
    if(param1<0.02){
        ofSetColor(255,100,100);
    }else if(param1>0.02){
        ofSetColor(180,100,100);
    }else if(param1>0.04){
        ofSetColor(130,100,100);
    }else if(param1>0.06){
        ofSetColor(80,100,100);
    }else if(param1>0.1){
        ofSetColor(20,100,100);
    }else if(param1>0.2){
        ofSetColor(100,0,100);
    }
    
    cube.draw();

    float angle = (ofGetElapsedTimef() * 1.4);
    
    
    cube.rotate(angle/100, angle/100, 0, 0);
    cube.set(ofClamp(param2*5, 20, 100));
    
    //drawing biggest cube
    if(param1 > 0.3){
        ofSetColor(50, 255, 50);
        cube.drawWireframe();
    }
    //drawing small cubes
    positionAndDrawCubes(cube,smallCubes);
    
}

//-----------------------------------------------------
void VisualsManager::drawSphereAndCones(float param1, float param2,float param3){
    
    sphere.setPosition(globalPosX, globalPosY,globalPosZ);
    sphere.setResolution(param3*20);
    
    ofSetColor(255);
    sphere.drawWireframe();

    for(int i=0;i<cones.size();i++){
        int x = cos(i)*110;
        int z = sin(i)*110;

        
        cones[i].setScale(fft->magnitudes[5+i]/8);
        cones2[i].setScale(fft->magnitudes[5+i]/8);

        if(param2>0.6){
            cones[i].setPosition(x, 0, z);
            cones2[i].setPosition(x,0, z);
        }else{
            cones[i].setPosition(x, -50, z);
            cones2[i].setPosition(x, 50, z);
        }
        
        if(param3>0.02){
            ofSetColor(ofRandom(250,120), ofRandom(50,110),ofRandom(100,120));
        }else if(param3>0.04){
            ofSetColor(ofRandom(100,120), ofRandom(150,110),ofRandom(100,120));
        }else if(param3>0.08){
            ofSetColor(ofRandom(255,180), ofRandom(50,110),ofRandom(100,120));

        }
        cones[i].draw();
        cones2[i].draw();
    }
    
    sphere.rotate(param1,0,param1,0);
    
}

//-----------------------------------------------------
void VisualsManager::drawCylinders(float param1, float param2, bool param3){
    
    //positioning cylinders
    for(int i = 0; i < cylinders.size(); i++){
        int x = cos(i)*100;
        int z = sin(i)*100;
        
        cylinders[i].set(20, 50);
        cylinders[i].setPosition(globalPosX+x, globalPosY, globalPosZ+z);
        
        tops.push_back(cylinders[i].getTopCapMesh());
        bottoms.push_back(cylinders[i].getBottomCapMesh());
    }

    
    if(clrScheme0){ //red
        ofSetColor(250-mfcc->melBands[(int)ofRandom(0,42)],fft->magnitudes[(int)ofRandom(0,42)] * 2,100);
    }else if(clrScheme1){//orange
        ofSetColor(255-mfcc->melBands[(int)ofRandom(0,42)],69+mfcc->melBands[(int)ofRandom(0,42)],100+fft->magnitudes[(int)ofRandom(0,42)] * 2);
        
    }else if(clrScheme2){//yellow
        ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100+fft->magnitudes[(int)ofRandom(0,42)] * 2);
        
    }else if(clrScheme3){//green
        ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100+fft->magnitudes[(int)ofRandom(0,42)] * 2);
        
    }else if (clrScheme4){//blue
        ofSetColor(0,(int)fft->magnitudes[(int)ofRandom(0,42)] * 2,255+mfcc->melBands[(int)ofRandom(0,42)]);
        
    }else if(clrScheme5){//indigo
        ofSetColor(75+(int)fft->magnitudes[(int)ofRandom(0,42)] * 2,0,130+mfcc->melBands[(int)ofRandom(0,42)]);
        
    }
    
    for(int i = 0; i < cylinders.size(); i++){
        cylinders[i].transformGL();
        //tops
//        ofSetColor(0,233+(int(fft->magnitudes[i] * 2)),100);
        ofPushMatrix(); {
            if(tops[i].getNumNormals() > 0) {

                ofTranslate(tops[i].getNormal(0) * fft->magnitudes[i] * 2 );
                tops[i].draw();
            }
        } ofPopMatrix();

        //bottoms
//        ofSetColor(233+(int(fft->magnitudes[i] * 2)),0,100);
        ofPushMatrix(); {
            if(bottoms[i].getNumNormals() > 0) {
                ofTranslate(bottoms[i].getNormal(0).x, bottoms[i].getNormal(0).y * (fft->magnitudes[i] * -2), bottoms[i].getNormal(0).z);
                bottoms[i].draw();
            }
        } ofPopMatrix();
        

       // cylinders[i].rotate(param1, 0,  0,param1);
        cylinders[i].restoreTransformGL();

        ofSetLineWidth(1);
        
//        if(param1>0.2){
//        ofSetColor(ofRandom(0,param2));
//        }else if(param1>0.4){
//            ofSetColor(255);
//        }else if(param1>0.6){
//            ofSetColor(ofRandom(0,param1*100));
//        }else if(param1>1){
//            ofSetColor(ofRandom(0,param1*100),100,200);
//        }
        
        
        if(clrScheme0){ //red
            ofSetColor(250-mfcc->melBands[(int)ofRandom(0,42)],0,100);
        }else if(clrScheme1){//orange
            ofSetColor(255-mfcc->melBands[(int)ofRandom(0,42)],69+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme2){//yellow
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if(clrScheme3){//green
            ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
            
        }else if (clrScheme4){//blue
            ofSetColor(75,0,255+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }else if(clrScheme5){//indigo
            ofSetColor(75,0,130+mfcc->melBands[(int)ofRandom(0,42)]);
            
        }
        
        
        if(param3){
            if(i%2 == 0){
                cylinders[i].drawWireframe();
            }
        }
    }
    
}



//-----------------------------------------------------
void VisualsManager::drawBoxesV3(float param1, float param2){
    
    for(int i = 0; i < boxesV3.size(); i++){
        boxesV3[i].setPosition(globalPosX, globalPosY,globalPosZ);
    }
    
    
    for(int i = 0; i < boxesV3.size(); i++){
        boxesV3[i].transformGL();
        for(int j = 0; j < ofBoxPrimitive::SIDES_TOTAL; j++ ) {
            ofPushMatrix();
            
            switch(rndmNum){
                case 0:
                    ofSetColor(0,100+(i+30),fft->magnitudes[i]*10);
                    break;
                case 1:
                    ofSetColor(0+(i*20),0,0);
                    break;
                case 2:
                    ofSetColor(0+(i*20),0,fft->magnitudes[i]*10);
                    break;
                case 3:
                    ofSetColor(0+(i*20),0,0);
                    break;
                case 4:
                    ofSetColor(fft->magnitudes[i]*10,0+(i*20),0);
                    break;
                case 5:
                    ofSetColor(0+(i*20),0,0);
                    break;
                case 6:
                    ofSetColor(0,fft->magnitudes[i]*10,0+(i*20));
                    break;
            }
            

            
            ofTranslate(boxesSidesV3[i][j].getNormal(0) * fft->magnitudes[i]*5);
            boxesSidesV3[i][j].drawFaces();
            ofPopMatrix();
        }
        
        boxesV3[i].restoreTransformGL();
    }
}


//--- End of draw
//-----------------------------------------------------
//--- Helper functions

//-----------------------------------------------------
void VisualsManager::positionAndDrawCubes(ofBoxPrimitive bigBox, vector <ofBoxPrimitive> &smallBoxes){
    
    if(clrScheme0){ //red
        ofSetColor(250-mfcc->melBands[(int)ofRandom(0,42)],0,100);
    }else if(clrScheme1){//orange
        ofSetColor(255-mfcc->melBands[(int)ofRandom(0,42)],69+mfcc->melBands[(int)ofRandom(0,42)],100);
        
    }else if(clrScheme2){//yellow
        ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
        
    }else if(clrScheme3){//green
        ofSetColor(255+mfcc->melBands[(int)ofRandom(0,42)],255+mfcc->melBands[(int)ofRandom(0,42)],100);
        
    }else if (clrScheme4){//blue
        ofSetColor(75,0,255+mfcc->melBands[(int)ofRandom(0,42)]);
        
    }else if(clrScheme5){//indigo
        ofSetColor(75,0,130+mfcc->melBands[(int)ofRandom(0,42)]);
        
    }
    
    smallBoxes[0].setPosition(0,0,(bigBox.getWidth()/2)+smallBoxes[0].getWidth()/2);
    smallBoxes[1].setPosition(0,0,(-bigBox.getWidth()/2)-smallBoxes[1].getWidth()/2);
    smallBoxes[2].setPosition(0,(bigBox.getWidth()/2)+smallBoxes[2].getWidth()/2,0);
    smallBoxes[3].setPosition(0,(-bigBox.getWidth()/2)-smallBoxes[3].getWidth()/2,0);
    smallBoxes[4].setPosition((bigBox.getWidth()/2)+smallBoxes[4].getWidth()/2,0,0);
    smallBoxes[5].setPosition((-bigBox.getWidth()/2)-smallBoxes[5].getWidth()/2,0,0);
    
    for(int i =0; i < smallBoxes.size(); i++){
        smallBoxes[i].draw();
    }
    
}

//--- Setting variables coming in from audio class
//-----------------------------------------------------
void VisualsManager::setRMS(float rms){
    RMS = rms;
}

//-----------------------------------------------------
void VisualsManager::setSpecFlatness(float sf){
    specFlatness = sf;
}

//-----------------------------------------------------
void VisualsManager::setSpecCentroid(float sc){
    specCentroid = sc;
}

//-----------------------------------------------------
void VisualsManager::setPeakFreq(float pf){
    peakFreq = pf;
}

//-----------------------------------------------------
//void VisualsManager::setFFTmagnitudes(float fftm){
//
////    FFTmags.push_back(fftm);
//    
//}

////-----------------------------------------------------
//void VisualsManager::setMFFCs(float mffcs){
//    MFFCs = mffcs;
//}
//
////-----------------------------------------------------
//void VisualsManager::setOctaveAverages(float oa){
//    octaveAverages = oa;
//}
//
////-----------------------------------------------------
//void VisualsManager::setPitchHistogram(float ph){
//    pitchHistogram = ph;
//}
//
////-----------------------------------------------------
//void VisualsManager::setMelBands(float mb){
//    melBands = mb;
//};

//-----------------------------------------------------
void VisualsManager::setIsBeat(bool beat){
    isBeat = beat;
}

//-----------------------------------------------------
void VisualsManager::setFFT(ofxMaxiFFT &mfft){
    fft = &mfft;
}

//-----------------------------------------------------
void VisualsManager::setMFCC(maxiMFCC &myMfcc){
    mfcc = &myMfcc;
}

//-----------------------------------------------------
void VisualsManager::setFFTOcatveAnalyzer(ofxMaxiFFTOctaveAnalyzer &myOctave){
    octaves = &myOctave;
    
}



