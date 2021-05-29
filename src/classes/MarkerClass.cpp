/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "MarkerClass.hpp"

/*
 * Stel marker in.
 */
void Marker::set(int _id, int _surfaceId, ofVec3f _position, ofVec3f _surfaceRotation, ofPoint _surfaceTopLeft, ofPoint _surfaceTopRight, ofPoint _surfaceBottomRight, ofPoint _surfaceBottomLeft, ofRectangle _layer)

{
	id = _id;
	surfaceId = _surfaceId;
	position = _position;

	surfaceRotation = _surfaceRotation;
	surfaceTopLeft = _surfaceTopLeft;
	surfaceTopRight = _surfaceTopRight;
	surfaceBottomRight = _surfaceBottomRight;
	surfaceBottomLeft = _surfaceBottomLeft;

	layer.x = 0;
	layer.y = 0;
	layer.width = WIDTH;
	layer.height = HEIGHT;

	return;
}