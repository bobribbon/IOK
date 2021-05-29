/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "ArucoHandler.hpp"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxAruco.h"

/*
 * Teken oppervlaktes op de gevonden markers.
 */
void ArucoHandler::draw(MarkerHandler *markerHandler, SurfaceHandler *surfaceHandler, int mode)
{
	vector<aruco::Marker> markers;
	
	framebuffer.begin();
	ofClear(0, 0, 0, 0);

	// teken camera
	if (mode & MODE_SHOW_CAMERA)
	{
		camera.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	markers = aruco.getMarkers();

	for (int i = 0; i < markerHandler->visibleMarkersId.size(); i++)
	{
		Marker marker = markerHandler->get(markerHandler->visibleMarkersId.at(i));

		aruco.begin(i);

		// teken sufaces
		if (marker.id != MARKER_UNKNOWN)
		{
			if (mode & MODE_EDIT && markerHandler->selectedMarkerId == marker.id)
			{
				surfaceHandler->draw(marker, true);
			}
			else
			{
				surfaceHandler->draw(marker);
			}
		}

		// teken marker
		if (mode & MODE_SHOW_MARKERS)
		{
			markerHandler->draw(marker);
		}

		aruco.end();
	}

	framebuffer.end();

	framebuffer.draw(0, 0);

	return;
}

/*
 * Verkrijg zichtbare markers id's.
 * Geeft een vector van ints terug met de gevonden id's.
 */
vector<int> ArucoHandler::getVisibleMarkersIds(void)
{
	vector<aruco::Marker> arucoMarkers;
	vector<int> ids;

	arucoMarkers = aruco.getMarkers();

	for (int i = 0; i < arucoMarkers.size(); i++)
	{
		ids.push_back(arucoMarkers.at(i).id);
	}

	return ids;
}

/*
 * Stel ofxAruco in.
 */
void ArucoHandler::setup(string dataPath)
{
	camera.setDeviceID(0);
	camera.initGrabber(WIDTH, HEIGHT);

	aruco.setup(dataPath + "intrinsics.int", camera.getWidth(), camera.getHeight());
	framebuffer.allocate(WIDTH, HEIGHT);

	return;
}

/*
 * Update camera.
 */
void ArucoHandler::update(int mode)
{
	if (mode & MODE_TRACK)
	{
		camera.update();

		if (camera.isFrameNew())
		{
			camera.getPixelsRef().mirror(true, false);
			aruco.detectBoards(camera.getPixels());
		}
	}

	return;
}