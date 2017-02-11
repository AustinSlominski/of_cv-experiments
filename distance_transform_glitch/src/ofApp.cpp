#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
 
    video.load("Wiretouch.MOV");
    video.play();
    video.setVolume(0);
    
    outImg.allocate(video.getWidth(),video.getHeight(),OF_IMAGE_GRAYSCALE);
    bw.allocate(video.getWidth(),video.getHeight(),OF_IMAGE_GRAYSCALE);

    webcam.initGrabber(ofGetWidth(),ofGetHeight());
    webcam.setup(ofGetWidth(),ofGetHeight());
    
    output_type = OF_IMAGE_COLOR_ALPHA;
    input_type  = OF_IMAGE_GRAYSCALE;
    
    gui_image.setup();
    gui_image.add(image_res.set("Resolution",ofPoint(video.getWidth(),video.getHeight()),ofPoint(0,0),ofPoint(video.getWidth(),video.getHeight())));
    gui_image.add(image_scale.set("Scale",1.0,0.0,1.0));
    gui_image.add(cv_thresh.set("Threshold",ofPoint(0,255),ofPoint(0,0),ofPoint(0,255)));
    gui_image.add(use_cam.set("Use Cam?",false));
    
    capture_frames = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    bool newFrame = video.isFrameNew();
    
    if(use_cam){
        webcam.update();
        newFrame = webcam.isFrameNew();
    }
    
    if(newFrame){
        if(use_cam){
            bw.setFromPixels(webcam.getPixels());
        }else{
            bw.setFromPixels(video.getPixels());
        }
        
        bw.setImageType(input_type);
//        bw.resize(image_res->x*image_scale,image_res->y*image_scale);
//        bw.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST); //prevents interpolation when dsampling
//        bw.update();
//        bw.resize(video.getWidth(),video.getHeight());
        
        /*---------------------
         DISTANCE TRANSFORM
         ---------------------*/
        Mat kernel = (Mat_<float>(3,3) <<
                      1,  1, 1,
                      1, -8, 1,
                      1,  1, 1);
        Mat dist;
        Mat t_src = toCv(bw.getPixels());
        Mat src;
        
        t_src.convertTo(src, CV_8UC1);
        
        threshold(src, src, cv_thresh->x,cv_thresh->y, CV_THRESH_BINARY | CV_THRESH_OTSU);
        
        ofPixels cvOut;
        
        distanceTransform(src, dist, CV_DIST_L2, 3);
        
        normalize(dist,dist,0.0,1.0,NORM_MINMAX);
        
        imshow("dist",dist);
        
        toOf(dist, cvOut);
        
        if(use_cam){
            outImg.setFromPixels(cvOut.getData(),webcam.getWidth(),webcam.getHeight(), output_type);
        }else{
            outImg.setFromPixels(cvOut.getData(),video.getWidth(),video.getHeight(), output_type);
        }
        
        outImg.update();
        
        if(capture_frames){
            ofSaveImage(outImg, "renders/"+ofToString(ofGetFrameNum())+".png" );
        }
    }
    
    video.nextFrame();
    video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    outImg.draw(0,0,ofGetWidth(),ofGetHeight());
    gui_image.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c'){
        capture_frames = !capture_frames;
    }
    if(key == '1'){
        output_type = OF_IMAGE_COLOR_ALPHA;
    }
    if(key == '2'){
        output_type = OF_IMAGE_COLOR;
    }
    if(key == '3'){
        output_type = OF_IMAGE_GRAYSCALE;
    }
    if(key == '4'){
        output_type = OF_IMAGE_UNDEFINED;
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
