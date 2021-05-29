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

#ifndef SurfaceHandler_hpp
#define SurfaceHandler_hpp

#include <stdio.h>
#include "classes/MarkerClass.hpp"
#include "classes/SurfaceClass.hpp"
#include "constants.hpp"
#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxXmlSettings.h"

/*
 * Verantwoordelijk voor het laden van de films en deze projecteren op de positie ingegeven door de markers
 */
class SurfaceHandler
{
public:
	void draw(Marker marker, bool outline = false);
	void load(string path);
	void reset(void);
	void setup(void);
	void start(void);
	void startInteraction(void);
	void update(void);

	Surface surfaces[MAX_SURFACES];

	ofFbo tempFramebuffer;
};

#endif