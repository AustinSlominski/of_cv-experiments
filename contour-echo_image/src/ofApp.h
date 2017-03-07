#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofImage image;
    ofxPanel cvGui, blastGui;
    ofxIntSlider nearThresh, farThresh;
    ofParameter<float> minArea, maxArea, threshold, sclOff;
    ofParameter<int> maxDev, numLayers;
    ofParameter<bool> holes;
    
    ofxCv::ContourFinder contourFinder;
    vector< vector<ofPolyline> > offsets;
    bool blast, offset;
    ofPoint v_point;
    
    //SYPHON OUT
    ofxSyphonServer mainOut;
    ofFbo outputFbo;
};
