#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxKinect.h"

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
    
    ofVideoPlayer video;
    ofVideoGrabber webcam;
    ofImage bw;
    ofImage outImg;
    
    ofImageType output_type, input_type;
    
    /* KINECT */
    ofxKinect kinect;
		
    bool capture_frames;
    
    ofxPanel gui_image;
    ofParameter<ofPoint> image_res, cv_thresh;
    ofParameter<float>   image_scale;
    ofParameter<bool>    use_cam;
};
