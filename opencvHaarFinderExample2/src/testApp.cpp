#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	img.loadImage("seinfield.jpeg");
	finder.setup("haarcascade_frontalface_default.xml");
	finder.findHaarObjects(img);
    ofSetVerticalSync(true);
    ofSetLineWidth(2);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	 
    img.draw(0, 0);
	ofNoFill();
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x , cur.y , cur.width, cur.height);
        
        ofSetColor(ofColor::white);
        
        
float ww =(cur.width);
        
    //    img.drawSubsection(1050, 200,ww, cur.height, cur.x, cur.y);
        
        img.drawSubsection(img.width+50, (i+cur.height/2)*3.3,ww, cur.height, cur.x, cur.y);
        
        //        img.drawSubsection(300, 200, 100,200,400);
        // img.drawSubsection(0,0,100,100,,100);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}