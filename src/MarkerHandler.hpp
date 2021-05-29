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

#ifndef MarkerHandler_hpp
#define MarkerHandler_hpp

#include <stdio.h>
#include "classes/MarkerClass.hpp"
#include "ofMain.h"
#include "ofxAruco.h"
#include "ofXml.h"
#include "ofxXmlSettings.h"

/*
 * Verantwoordelijk voor het inladen van de markerinstellingen
 */
class MarkerHandler
{
public:
	void draw(Marker marker);
	void edit(Marker *marker, int item, int value);
	Marker get(int id);
	vector<string> getInfo(Marker marker);
	void loadMarkers(std::string path);
	void save(Marker marker, std::string path);
	void update(Marker marker);

	ofxXmlSettings xml;
	ofxXmlSettings settings;

	vector<Marker> markers;
	vector<int> visibleMarkersId;

	int selectedMarkerId;
};

#endif
