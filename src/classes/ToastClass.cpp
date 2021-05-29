/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "ToastClass.hpp"

/*
 * Druk de boodschap af als de timer niet verlopen is.
 */
void Toast::print(void)
{
	if (ofGetUnixTime() - timer < timeout)
	{
		ofDrawBitmapStringHighlight(message, ofGetWidth() / 2 - ((message.size() * FONT_WIDTH) / 2), ofGetHeight() - 2 * FONT_HEIGHT, ofColor::blue, ofColor::yellow);
	}
	else
	{
		message = "";
	}

	return;
}

/*
 * Stel een nieuwe boodschap in.
 */
void Toast::set(std::string _message, int _timeout)
{
	message = _message;
	timer = ofGetUnixTime();
	timeout = _timeout;

	return;
}
