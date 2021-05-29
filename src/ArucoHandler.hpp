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

#ifndef ArucoHandler_hpp
#define ArucoHandler_hpp

#include <stdio.h>
#include "classes/MarkerClass.hpp"
#include "constants.hpp"
#include "MarkerHandler.hpp"
#include "ofMain.h"
#include "ofxAruco.h"
#include "SurfaceHandler.hpp"

/*
 * Verantwoordelijk voor het detecteren van de positie en oriëntatie van de markers.
 */
class ArucoHandler
{
public:
	void draw(MarkerHandler *markerHandler, SurfaceHandler *surfaceHandler, int mode);
	vector<int> getVisibleMarkersIds(void);
	void setup(string dataPath);
	void update(int mode);

	ofxAruco aruco;
	ofFbo checkerboardTex;
	ofFbo framebuffer;
	ofVideoGrabber camera;
};

#endif
