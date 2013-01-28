#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	ofBackground(99);
  
//	ofBackground(255,255,255);
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	
	width = 10;
    
	ofxAnimatableFloat f;
	f.animateFromTo( 300, 500 );
	f.setDuration(2);
	f.setRepeatType( LOOP_BACK_AND_FORTH );
	
	for ( int i = 0; i < NUM_ANIM_CURVES; i++ ){
		pos[i] = f;
		AnimCurve curve = (AnimCurve) (EASE_IN_EASE_OUT + i );
		pos[i].setCurve( curve );
		curveNames[i] = ofxAnimatable::getCurveName( curve );
	}
    
	ball.reset(300);
	ball.setCurve(EASE_IN);
	ball.setRepeatType(LOOP_BACK_AND_FORTH);
	ball.setDuration(0.55);
	ball.animateTo( 400 );
	
	colorAnim.setColor( ofColor::black );
	colorAnim.setDuration( 0.5f );
	colorAnim.setRepeatType(LOOP_BACK_AND_FORTH);
	colorAnim.setCurve(LINEAR);
	colorAnim.animateTo( ofColor::white );
	
	pointAnim.setPosition( ofPoint(100,100) );
	pointAnim.setRepeatType(PLAY_ONCE);
	pointAnim.setCurve(EASE_IN_EASE_OUT);
    
    
	pointAnim2.setPosition( ofPoint(100,100) );
	pointAnim2.setRepeatType(PLAY_ONCE);
	pointAnim2.setCurve(EASE_IN_EASE_OUT);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    //app timebase, to send to all animatable objets
	float dt = 1.0f / ofGetFrameRate();
	
	for ( int i = 0; i < NUM_ANIM_CURVES; i++ )
		pos[i].update( dt );
	
	ball.update( dt );
	
	colorAnim.update( dt );
	pointAnim.update( dt );
    pointAnim2.update( dt );
    
	if ( !pointAnim.isOrWillBeAnimating() ){
		pointAnim.animateToAfterDelay( ofPoint( ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), 0.5);
	}
    
	if ( !pointAnim2.isOrWillBeAnimating() ){
		pointAnim2.animateToAfterDelay( ofPoint( ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), 0.5);
	}
    
	//animate our parametric curves
	float a = 0.5 + 0.5 * sin( 0.1 * ofGetFrameNum());
	float b = 0.5 + 0.5 * sin( 0.1 * ofGetFrameNum() + 400);
	pos[QUADRATIC_BEZIER_PARAM].setQuadraticBezierParams( a, b);
    
	float steep = 0.5 + 0.5 * sin( 0.1 * ofGetFrameNum());
	pos[EXPONENTIAL_SIGMOID_PARAM].setDoubleExpSigmoidParam( steep );

    ////stuffs
    
    
    for (int i = 0; i < line.getVertices().size(); i++){
        
        if (ofGetMousePressed() == false){
            float distance = ofDist(mouseX, mouseY, line.getVertices()[i].x, line.getVertices()[i].y);
            if (distance < 100){
                
                float pct = ofMap(distance, 0,100, 1,0);
                
                ofPoint diff = ofPoint(mouseX, mouseY) - ofPoint(line.getVertices()[i].x, line.getVertices()[i].y);
                diff.normalize();
                
                line.getVertices()[i].x += diff.x * 2 *  pct;
                line.getVertices()[i].y += diff.y * 2 * pct;
                
            }
        }
        
        
    }
    for (int i = 0; i < line.getVertices().size(); i++){
          if (ofGetMousePressed() == false){

          }
    }
    
    

    
    

}

//--------------------------------------------------------------
void testApp::draw(){

    
	ofBackground(99);
    
    
    
    //ofBackgroundGradient(ofColor::white, ofColor(200,200,200), OF_GRADIENT_LINEAR);
    
    colorAnim.applyCurrentColor();
	
    //ofCircle( ( 9 * ofGetFrameNum() )%ofGetWidth(), ball.val(), width);
	//glColor4ub(255,255,255,255);
	//ofRect(0, 400 + width, ofGetWidth(), 1);
	
    //vertical lines
//	ofRect(300, 0, 1, 400 + width);
//	ofRect(500+width, 0, 1, 300 + width);
    
    glColor4f( pointAnim.getPercentDone(), 1 - pointAnim.getPercentDone() , 0, 1);
	glPointSize(50);
	pointAnim.draw();
    //
    pointAnim.getCurrentPosition() ;
    
    
    glColor4f( pointAnim2.getPercentDone(), 4 - pointAnim2.getPercentDone() , 0, 1);
	glPointSize(10);
    pointAnim2.draw();
    
	//glColor4ub(255,255,255,255);
	ofDrawBitmapString( ofToString( ofGetFrameRate()),  10, 10);
	 

    
	int vOff = 10;
	for ( int i = 0 ; i < NUM_ANIM_CURVES; i++ ){
		float lineHeight = 4.0;
		float yy = vOff + i * lineHeight * width;
		glColor4ub(255,255,255,64);
		ofLine(300, yy + width * 0.5, 500 + width, yy + width * 0.5);
		glColor4ub(255,255,255,255);
		ofRect( pos[i].val(), yy, width*1.5, width*1.5);
		ofDrawBitmapString(  curveNames[i] + "  vel: " +ofToString( pos[i].getCurrentSpeed(), 2), 515, yy + 10);
	
        line.draw();
        mesh.draw();

 
        
        
        
    }
 

	}




void testApp::drawPlot(int x, int y, int size, AnimCurve curve, string title){
    
	int xx = x;
	int yy = y;
	float s = size;
	float steps = size;
	ofxAnimatableFloat a = pos[curve];
	a.setCurve(curve);
	a.setDuration(1);
	a.reset(0);
	a.animateTo(1);
	a.drawCurve(x, y, size);
}


 



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
 
        
        ofPolyline lineRespaced = line;
        
        // add the last point (so when we resample, it's a closed polygon)
        lineRespaced.addVertex(lineRespaced[0]);
        // resample
        lineRespaced = lineRespaced.getResampledBySpacing(20);
        // I want to make sure the first point and the last point are not the same, since triangle is unhappy:
        lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
        // if we have a proper set of points, mesh them:
        if (lineRespaced.size() > 5){
            
            // angle constraint = 28
            // size constraint = -1 (don't constraint triangles by size);
            
            //            mesh.triangulate(lineRespaced, 28, -1);
            
            
            // this is an alternative, constrain on size not angle:
            mesh.triangulate(lineRespaced, -1, 200);
            
            // see ofxTriangleMesh.h for info.
            
        }
        
        int nPts =  line.getVertices().size();
        line = line.getResampledByCount(nPts * 5);
   

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    
    line.addVertex(ofPoint(x, y));
    
   }

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  line.clear();
    line.addVertex(ofPoint(x, y));
 	pointAnim.animateTo( ofPoint(x, y) );
    pointAnim2.animateTo( ofPoint(x, y) );
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
 
        
        ofPolyline lineRespaced = line;
        
        // add the last point (so when we resample, it's a closed polygon)
        lineRespaced.addVertex(lineRespaced[0]);  
        // resample
        lineRespaced = lineRespaced.getResampledBySpacing(20);
        // I want to make sure the first point and the last point are not the same, since triangle is unhappy: 
        lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
        // if we have a proper set of points, mesh them: 
        if (lineRespaced.size() > 5){
            
            // angle constraint = 28
            // size constraint = -1 (don't constraint triangles by size);
            
//            mesh.triangulate(lineRespaced, 28, -1);
            
            
            // this is an alternative, constrain on size not angle: 
              mesh.triangulate(lineRespaced, -1, 200);
            
            // see ofxTriangleMesh.h for info. 
            
        }
        
        int nPts =  line.getVertices().size();
        line = line.getResampledByCount(nPts * 5);
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