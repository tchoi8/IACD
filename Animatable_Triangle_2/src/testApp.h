//#ifndef _TEST_APP
#define _TEST_APP

#pragma once

#include "ofMain.h"
#include "ofxTriangleMesh.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
        ofPolyline line;
    
        ofxTriangleMesh mesh;
    
        //shits from Animatable
        void drawPlot(int x, int y, int size, AnimCurve curve, string title);
        float position;
    
        ofxAnimatableFloat pos[NUM_ANIM_CURVES];
        string curveNames[NUM_ANIM_CURVES];
	
        ofxAnimatableFloat ball;
	
        ofxAnimatableOfColor	colorAnim;
        ofxAnimatableOfPoint	pointAnim;
         ofxAnimatableOfPoint	pointAnim2;
        float width;
        float fr;

    
    
};
