// http://www.astronexus.com/node/34
// https://github.com/astronexus/HYG-Database


#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    
    ofBackground( 10 );
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    ofSetCircleResolution(64);
    
    csv.loadFile(ofToDataPath("hygxyz.csv"));
    
    //    glPointSize(1);
    
    easyCam.rotate(-10, 1, 0, 0);
    easyCam.setDistance(300);
    
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
    
    float connectionDistanceStar = 40;
    int numberStars = starLineMesh.getNumVertices();
    
    for (int i=0; i<numberStars; i+=50) {
        ofVec3f verFirst = starLineMesh.getVertex(i);
        for (int j=i+1; j<numberStars; j+=50) {
            ofVec3f verSecond = starLineMesh.getVertex(j);
            float distance = verFirst.distance(verSecond);
            if (distance < connectionDistanceStar) {
                starLineMesh.addIndex(i);
                starLineMesh.addIndex(j);
                countLine++;
            }
        }
    }
    
    cout << csv.data[0][14] << endl;
    
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
    
    ofColor centerColor = ofColor(35, 28, 18);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    
    ofRotateY(rotY);
    drawingCircle(90);
    
    starMesh.setMode(OF_PRIMITIVE_POINTS);
    starMesh.draw();
    starLineMesh.setMode(OF_PRIMITIVE_LINES);
    starLineMesh.draw();
    
    easyCam.end();
    
    ofSetColor(255);
    ofDrawBitmapString( ofToString(ofGetFrameRate()), 10, 20 );
    ofDrawBitmapString( "starNum : " + ofToString( starMesh.getNumVertices() ), 10, 40 );
    ofDrawBitmapString( "lineNum : " + ofToString( countLine ), 10, 60 );
    
    ofDrawBitmapString( "StarData : https://github.com/astronexus/HYG-Database", 10, ofGetHeight()-20 );
    
}


void ofApp::drawingCircle(int _degX){
    
    ofPushMatrix();
    ofRotateX(_degX);
    for (int i=0; i<20; i++) {
        ofNoFill();
        ofSetColor(255,ofMap(i,0,19,140,0));
        ofCircle(0, 0, 50+i*i);
    }
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='f') {
        ofToggleFullscreen();
    }
    
}






void ofApp::keyReleased(int key){
    
}


void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
