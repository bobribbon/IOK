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

#ifndef SurfaceClass_hpp
#define SurfaceClass_hpp

#include "classes/LayerClass.hpp"
#include "constants.hpp"
#include "ofMain.h"
#include "ofxHapPlayer.h"

/*
 * Oppervlakte met verschillende lagen.
 */
class Surface
{
public:
	Surface(void);

	Layer			layers[MAX_LAYERS];
	ofFbo			framebuffer;

	int				id;
	int				interactionLayerId;
};

#endif