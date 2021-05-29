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

#ifndef constants_hpp
#define constants_hpp

#define WIDTH				1024
#define HEIGHT				768

#define FONT_WIDTH			8
#define FONT_HEIGHT			11

#define MARKER_UNKNOWN		-1

#define MAX_VOLUME			5
#define SOUND_INACTIVE		-1

#define MAX_SURFACES		5
#define SURFACE_INACTIVE	-1
#define SURFACE_WALL		0
#define SURFACE_CEILING		1

#define MAX_LAYERS			5
#define LAYER_INACTIVE		-1
#define LAYER_BACKGROUND	0
#define LAYER_INTERACTION	1
#define LAYER_FOREGROUND	2

#define MODE_EDIT			1
#define MODE_INTERACTION	2
#define MODE_MUTE			4
#define MODE_SHOW_CAMERA	8
#define MODE_SHOW_FPS		16
#define MODE_SHOW_MARKERS	32
#define MODE_SHOW_HELP		64
#define MODE_SHOW_TOAST		128
#define MODE_TRACK			256

#endif