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

#include "ArucoHandler.hpp"
#include "classes/MarkerClass.hpp"
#include "classes/ToastClass.hpp"
#include "constants.hpp"
#include "MarkerHandler.hpp"
#include "ofMain.h"
#include "SurfaceHandler.hpp"

/*
 * openframeworks app
 */
class ofApp : public ofBaseApp
{
public:
	#define storyPath	dataPath + "stories/" + stories[currentStory] + "/"
	#define markersPath	storyPath + "markers/";
	#define moviesPath	storyPath + "movies/";

	void draw(void);
	void keyPressed(int key);
	void loadSettings(void);
	void loadSounds(void);
	vector<string> loadStories(void);
	void selectStory(void);
	void setup(void);
	void update(void);

	ArucoHandler arucoHandler;
	ofSoundPlayer interactionSound;
	MarkerHandler markerHandler;
	ofSoundPlayer backgroundSound;
	SurfaceHandler surfaceHandler;
	Toast toast;
	
	vector<string> info;	
	vector<string> stories;

	int currentInfo = 0;
	int currentMarker = 0;
	int currentStory = 0;
	
	string dataPath;
	int framerate;
	int mode = 0;
	int volume = 5;
};