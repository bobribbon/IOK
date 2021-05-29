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

#ifndef LayerClass_hpp
#define LayerClass_hpp

#include "constants.hpp"
#include "ofMain.h"
#include "ofxHapPlayer.h"

/*
 *
 */
class Layer
{
public:
	ofxHapPlayer	movie;

	int				id = LAYER_INACTIVE;
};

#endif