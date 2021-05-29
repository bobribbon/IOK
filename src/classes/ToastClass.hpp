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

#ifndef ToastClass_hpp
#define ToastClass_hpp

#include <string>
#include "constants.hpp"
#include "ofMain.h"

/*
 * Toon een bericht op het scherm voor een bepaalde tijd
 */
class Toast
{
public:
	void print(void);
	void set(std::string _message, int _timeout = 3);

	int	timer;
	int	timeout;
	std::string	message;
};

#endif