/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#pragma once

#ifndef MarkerClass_hpp
#define MarkerClass_hpp

#include <stdio.h>
#include "constants.hpp"
#include "ofPoint.h"
#include "ofRectangle.h"
	
class Marker
{
public:
	#define MARKER_NUM_VARIABLES 19

	void set(int _id, int _surfaceId, ofVec3f _position, ofVec3f _surfaceRotation, ofPoint _surfaceTopLeft, ofPoint _surfaceTopRight, ofPoint _surfaceBottomRight, ofPoint _surfaceBottomLeft, ofRectangle _layer);

    int id = MARKER_UNKNOWN;
	int surfaceId = SURFACE_INACTIVE;
	ofVec3f position;

	ofVec3f surfaceRotation;
	ofPoint surfaceTopLeft = { 0.0, 0.0 };
	ofPoint surfaceTopRight = { WIDTH, 0.0 };
	ofPoint surfaceBottomRight = { WIDTH, HEIGHT };
	ofPoint surfaceBottomLeft = { 0.0, HEIGHT };

	ofRectangle layer;
};

#endif