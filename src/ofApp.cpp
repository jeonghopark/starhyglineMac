// http://www.astronexus.com/node/34
// https://github.com/astronexus/HYG-Database


#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
#ifdef DEBUG
    
#else
    ofSetDataPathRoot("../Resources/data/");
#endif
    
    
    
    ofBackground( 10 );
    
    //    ofEnableArbTex();
    ofEnableDepthTest();
    ofDisableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    ofSetCircleResolution(64);
    
    csv.loadFile(ofToDataPath("hygxyz.csv"));
    
    //    glPointSize(1);
    
    easyCam.rotate(-10, 1, 0, 0);
    easyCam.setDistance(300);
    
    
    
    
    if (csv.data.size()>0) {
        
        for(int i=1; i<csv.numRows; i++) {
            
            float tempX = ofToFloat( csv.data[i][17] );
            float tempY = ofToFloat( csv.data[i][18] );
            float tempZ = ofToFloat( csv.data[i][19] );
            float tempBright = ofMap( ofToFloat( csv.data[i][14] ), 40, -10, 0, 255 );
            
            ofVec3f _position( tempX, tempY, tempZ );
            starMesh.addVertex( _position );
            //        zPositionFactor.push_back(tempZ);
            
            ofColor c (tempBright,tempBright,tempBright,80);
            starMesh.addColor( c );
            
            
        }
        
        starLineMesh = starMesh;
        
        float _distanceStarT = 40;
        int numberStars = starLineMesh.getNumVertices();
        
        for (int i=0; i<numberStars; i+=50) {
            ofVec3f verFirst = starLineMesh.getVertex(i);
            starLineMesh.addVertex( verFirst );
            
            for (int j=0; j<numberStars; j+=50) {
                ofVec3f verSecond = starLineMesh.getVertex(j);
                starLineMesh.addVertex( verSecond );
                float distance = verFirst.distance(verSecond);
                if ((distance < _distanceStarT)) {
                    starLineMesh.addIndex(i);
                    starLineMesh.addIndex(j);
                    ofColor c (255);
                    starLineMesh.addColor( c );
                }
            }
            
        }
        
        
    }
    
    
    
}




//--------------------------------------------------------------
void ofApp::update(){
    
    rotY = rotY + 0.1;
    
    sinY = sin(ofDegToRad(rotY));
    
    int numberVerts = starMesh.getNumVertices();
    for (int i=0; i<numberVerts; i++) {
        ofVec3f temp = starMesh.getVertex(i);
        temp.x = temp.x;
        temp.y = temp.y;
        temp.z = temp.z;
        starMesh.setVertex( i, temp );
    }
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    //    ofColor centerColor = ofColor(35, 28, 18);
    //    ofColor edgeColor(0, 0, 0);
    //    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    
    ofRotateY(rotY);
    drawingCircle(90);
    
    starMesh.setMode(OF_PRIMITIVE_POINTS);
    starLineMesh.setMode(OF_PRIMITIVE_LINES);
    starMesh.draw();
    starLineMesh.draw();
    
    easyCam.end();
    
    
    ofPushStyle();
    ofSetColor(255);
    ofDrawBitmapString( ofToString(ofGetFrameRate()), 10, 20 );
    ofDrawBitmapString( "starNum : " + ofToString( starMesh.getNumVertices() ), 10, 40 );
    ofDrawBitmapString( "lineNum : " + ofToString( starLineMesh.getNumVertices() ), 10, 60 );
    ofDrawBitmapString( "StarData : https://github.com/astronexus/HYG-Database", 10, ofGetHeight()-20 );
    ofPopStyle();
    
}


//--------------------------------------------------------------
void ofApp::exit(){
    
    std::exit(0);
    
}




//--------------------------------------------------------------
void ofApp::drawingCircle(int _degX){
    
    ofPushMatrix();
    ofRotateX(_degX);
    for (int i=0; i<20; i++) {
        ofNoFill();
        ofSetColor( 255, ofMap(i,0,19,140,0));
        ofDrawCircle(0, 0, 50+i*i);
    }
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='f') {
        ofToggleFullscreen();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
