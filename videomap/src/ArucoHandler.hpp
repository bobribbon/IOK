//
//  ArucoHandler.cpp
//  TeamScheireV2
//
//  Created by Jan Everaert on 07/10/2019.
//

#ifndef ArucoHandler_hpp
#define ArucoHandler_hpp

#include "ArucoHandler.hpp"

#include <stdio.h>
#include "ofMain.h"

#include "ofxAruco.h"
#include "SurfaceGenerator.hpp"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"
#include "MarkerClass.hpp"
#include "ofXml.h"
#include "ofxGui.h"

class ArucoHandler
{
public:
	void setup(ofxOscSender s);
	void update();
	void draw(SurfaceGenerator *surfaces, bool DEBUG_MODE, bool DISPLAY_INTERACTION, bool DISPLAY_LOUIS, bool DISPLAY_CAM);
	void setupSurfaces();

	void handleOSC(ofxOscMessage msg);
	void drawFile(SurfaceGenerator *surfaces, vector<aruco::Marker> markers, bool DEBUG_MODE);
	void drawOSC(SurfaceGenerator *surfaces, vector<aruco::Marker> markers, bool DEBUG_MODE);
	void sendMessage(string channel, int value);
	void saveButtonPressed();

	ofxAruco aruco;
	ofVideoGrabber grabber;
	ofBaseVideoDraws *trackVideo;

	ofxOscSender sender;

	ofxXmlSettings xml;
	ofxXmlSettings settings;

	ofxPanel gui;
	ofxVec3Slider translate;
	ofxVec3Slider rotate;
	ofxButton saveBtn;
	ofFbo fbo;

	vector<MarkerClass> markerList;

	bool TRACK = true;
	bool INTERACTION = false;
	bool LOUIS = false;

	float OSCScale = 0.001;
	int OSCOutputX = 0;
	int OSCOutputY = 0;
	int OSCOutputZ = 0;
	int OSCOutputWidth = 200;
	int OSCOutputHeight = 200;
	int OSCVideoX = 0;
	int OSCVideoY = 0;
	int OSCVideoWidth = 1024;
	int OSCVideoHeight = 512;
	int OSCPosition = 0;

	int curID = 0;
};

#endif /* MarkerClass_hpp */
