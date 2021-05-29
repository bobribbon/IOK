/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "ofMain.h"
#include "ofApp.hpp"

/*
 * Entrypoint
 */

int main()
{
	//ofSetupOpenGL(WIDTH, HEIGHT, OF_FULLSCREEN);
	ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW);

	//ofSetEscapeQuitsApp(false);

	ofRunApp(new ofApp());
}