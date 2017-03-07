#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    
    image.load("img/slipknot.jpg");
    
    cvGui.setup("CV","",0,80);
    cvGui.add(minArea.set("Min area", 10, 1, 100));
    cvGui.add(maxArea.set("Max area", 200, 1, 500));
    cvGui.add(threshold.set("Threshold", 128, 0, 255));
    cvGui.add(holes.set("Holes", false));
    
    blastGui.setup("BLAST","",0,180);
    blastGui.add(sclOff.set("Offset Scalar", 1., 0., 2.));
    blastGui.add(numLayers.set("Number of Layers", 2, 0, 10));
    blastGui.add(maxDev.set("Max Dev", 5, 0, 100));
    
    ofSetFrameRate(30);
    outputFbo.allocate(image.getWidth(),image.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    outputFbo.begin();
    ofClear(0,0,0,150);
    outputFbo.end();
    
    contourFinder.setMinAreaRadius(minArea);
    contourFinder.setMaxAreaRadius(maxArea);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(image);
    contourFinder.setFindHoles(holes);
    contourFinder.setSimplify(true);
    
    /*---------------------
     VECTOR INIT
     ---------------------*/
    if(offsets.size() != contourFinder.size()){
        offsets.resize(contourFinder.size());
    }
    
    for(int i = 0; i < contourFinder.size(); i++){
        vector <ofPolyline> poly_vec;
        ofPolyline & poly = contourFinder.getPolyline(i);
        poly.simplify();
        
        poly_vec.push_back(poly.getSmoothed(0.5));
        
        for(int j = 0; j < numLayers; j++){
            ofPolyline & poly = poly_vec[0];
            
            
            for(int k = 0; k < poly.size(); k++){
                ofPoint & point = poly[k];
                
                if(blast){
                    point.x = point.x + int(ofRandom(maxDev));
                    point.y = point.y + int(ofRandom(maxDev));
                }
                point = ((point-v_point) * ofPoint(sclOff,sclOff)) + v_point;
            }
            
            //smoothing, don't know if it works really
            poly.close();
            
            poly_vec.push_back(poly.getSmoothed(2));
        }
        offsets[i] = poly_vec;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    image.draw(0,0);
    outputFbo.begin();
    for(int i = 0; i < offsets.size(); i++){
        for(int j = 0; j < offsets[i].size(); j++){
            offsets[i][j].draw();
        }
    }
    outputFbo.end();
    
    outputFbo.draw(0,0);
    
    if(blast){
        ofDrawBitmapString("BLAST",ofGetWidth()-100,ofGetHeight()-20);
    }
    
    mainOut.publishScreen();
    
    cvGui.draw();
    blastGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        blast = !blast;
    }
    
    if(key == 'o'){
        offset = !offset;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    v_point.x = x;
    v_point.y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
