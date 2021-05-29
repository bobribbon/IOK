/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "MarkerHandler.hpp"

/*
 * Omlijn gevonden marker en teken het assenstelsel.
 */
void MarkerHandler::draw(Marker marker)
{
	ofPushMatrix();

	ofPushStyle();

	// omkader marker
	if (marker.id == selectedMarkerId)
	{
		ofSetLineWidth(5);
		ofSetColor(ofColor::yellow);
	}
	else
	{
		ofSetLineWidth(1);
		ofSetColor(ofColor::white);
	}
	ofNoFill();
	ofDrawRectangle(-0.15 / 2, -0.15 / 2, 0.15, 0.15); // corrigeren omdat oorsprong in het midden van de marker valt

	ofPopStyle();
	ofPushStyle();

	// teken assen
	ofDrawAxis(0.15);
	// teken id
	ofDrawBitmapString(marker.id, 0, 0);
	
	ofPopStyle();

	ofPopMatrix();

	return;
}

/*
 * Bewerk marker element.
 */
void MarkerHandler::edit(Marker *marker, int item, int value)
{
	switch (item)
	{
	case 1:
		marker->surfaceId += value;
		break;
	case 2:
		marker->position.x += value;
		break;
	case 3:
		marker->position.y += value;
		break;
	case 4:
		marker->position.z += value;
		break;

	case 5:
		marker->surfaceRotation.x += value;
		break;
	case 6:
		marker->surfaceRotation.y += value;
		break;
	case 7:
		marker->surfaceRotation.z += value;
		break;
	case 8:
		marker->surfaceTopLeft.x += value;
		break;
	case 9:
		marker->surfaceTopLeft.y += value;
		break;
	case 10:
		marker->surfaceTopRight.x += value;
		break;
	case 11:
		marker->surfaceTopRight.y += value;
		break;
	case 12:
		marker->surfaceBottomRight.x += value;
		break;
	case 13:
		marker->surfaceBottomRight.y += value;
		break;
	case 14:
		marker->surfaceBottomLeft.x += value;
		break;
	case 15:
		marker->surfaceBottomLeft.y += value;
		break;

	case 16:
		marker->layer.x += value;
		break;
	case 17:
		marker->layer.y += value;
		break;
	case 18:
		marker->layer.width += value;
		break;
	case 19:
		marker->layer.height += value;
		break;
	}

	return;
}

/*
 * Verkrijg marker op basis van id.
 * Geeft een Marker object terug.
 */
Marker MarkerHandler::get(int id)
{
	for (int i = 0; i < markers.size(); i++)
	{
		if (markers.at(i).id == id)
		{
			return markers.at(i);
		}
	}

	// id niet gevonden?
	Marker marker;
	marker.id = id;

	return marker;
}

/*
 * Verkrijg informatie.
 * Geeft een vector van strings terug met de informatie.
 */
vector<string> MarkerHandler::getInfo(Marker marker)
{
	vector<string> info;

	info.push_back("id:                  " + to_string(marker.id));
	info.push_back("surfaceId:           " + to_string(marker.surfaceId));
	info.push_back("x:                   " + to_string(marker.position.x));
	info.push_back("y:                   " + to_string(marker.position.y));
	info.push_back("z:                   " + to_string(marker.position.z));

	info.push_back("surfaceRotationX:    " + to_string(marker.surfaceRotation.x));
	info.push_back("surfaceRotationY:    " + to_string(marker.surfaceRotation.y));
	info.push_back("surfaceRotationZ:    " + to_string(marker.surfaceRotation.z));
	info.push_back("surfaceTopLeftX:     " + to_string(marker.surfaceTopLeft.x));
	info.push_back("surfaceTopLeftY:     " + to_string(marker.surfaceTopLeft.y));
	info.push_back("surfaceTopRightX:    " + to_string(marker.surfaceTopRight.x));
	info.push_back("surfaceTopRightY:    " + to_string(marker.surfaceTopRight.y));
	info.push_back("surfaceBottomRightX: " + to_string(marker.surfaceBottomRight.x));
	info.push_back("surfaceBottomRightY: " + to_string(marker.surfaceBottomRight.y));
	info.push_back("surfaceBottomLeftX:  " + to_string(marker.surfaceBottomLeft.x));
	info.push_back("surfaceBottomLeftY:  " + to_string(marker.surfaceBottomLeft.y));

	info.push_back("layerX:              " + to_string(marker.layer.x));
	info.push_back("layerY:              " + to_string(marker.layer.y));
	info.push_back("layerWidth:          " + to_string(marker.layer.width));
	info.push_back("layerHeight:         " + to_string(marker.layer.height));

	return info;
}

/*
 * Laad de ingestelde markers uit de map /markers.
 */
void MarkerHandler::loadMarkers(string path)
{
	path += "markers/";

	ofDirectory dir(path);
	string markersFound;

	markers.clear();

	dir.allowExt("xml");
	dir.listDir();

	for (int i = 0; i < dir.size(); i++)
	{
		Marker marker;
		ofxXmlSettings xml;

		if (xml.loadFile(path + dir.getName(i)))
		{
			xml.pushTag("marker");

			marker.set(
				xml.getValue("id", MARKER_UNKNOWN),
				xml.getValue("surfaceid", SURFACE_INACTIVE),
				ofVec3f(xml.getValue("position:x", 0), xml.getValue("position:y", 0), xml.getValue("position:z", 0)),

				ofVec3f(xml.getValue("surfacerotation:x", 0), xml.getValue("surfacerotation:y", 0), xml.getValue("surfacerotation:z", 0)),
				ofPoint((float)xml.getValue("surfacetopleft:x", 0), (float)xml.getValue("surfacetopleft:y", 0)),
				ofPoint((float)xml.getValue("surfacetopright:x", 0), (float)xml.getValue("surfacetopright:y", 0)),
				ofPoint((float)xml.getValue("surfacebottomright:x", 0), (float)xml.getValue("surfacebottomright:y", 0)),
				ofPoint((float)xml.getValue("surfacebottomleft:x", 0), (float)xml.getValue("surfacebottomleft:y", 0)),

				ofRectangle(xml.getValue("layer:x", 0), xml.getValue("layer:y", 0), xml.getValue("layer:width", 0), xml.getValue("layer:height", 0))
			);

			xml.popTag();
		}

		markers.push_back(marker);
		markersFound = markersFound + dir.getName(i) + " ";
	}

	ofLog() << to_string(markers.size()) << " marker files loaded (" << markersFound << ")";

	return;
}

/*
 * Sla marker op als <id>.xml.
 */
void MarkerHandler::save(Marker marker, std::string path)
{
	ofxXmlSettings xml;

	xml.setValue("marker:id", (int)marker.id);
	xml.setValue("marker:surfaceid", (int)marker.surfaceId);
	xml.setValue("marker:position:x", (int)marker.position.x);
	xml.setValue("marker:position:y", (int)marker.position.y);
	xml.setValue("marker:position:z", (int)marker.position.z);

	xml.setValue("marker:surfacerotation:x", (int)marker.surfaceRotation.x);
	xml.setValue("marker:surfacerotation:y", (int)marker.surfaceRotation.y);
	xml.setValue("marker:surfacerotation:z", (int)marker.surfaceRotation.z);

	xml.setValue("marker:surfacerotation:x", (int)marker.surfaceRotation.x);
	xml.setValue("marker:surfacerotation:y", (int)marker.surfaceRotation.y);
	xml.setValue("marker:surfacerotation:z", (int)marker.surfaceRotation.z);

	xml.setValue("marker:surfacetopleft:x", (int)marker.surfaceTopLeft.x);
	xml.setValue("marker:surfacetopleft:y", (int)marker.surfaceTopLeft.y);
	xml.setValue("marker:surfacetopright:x", (int)marker.surfaceTopRight.x);
	xml.setValue("marker:surfacetopright:y", (int)marker.surfaceTopRight.y);
	xml.setValue("marker:surfacebottomright:x", (int)marker.surfaceBottomRight.x);
	xml.setValue("marker:surfacebottomright:y", (int)marker.surfaceBottomRight.y);
	xml.setValue("marker:surfacebottomleft:x", (int)marker.surfaceBottomLeft.x);
	xml.setValue("marker:surfacebottomleft:y", (int)marker.surfaceBottomLeft.y);

	xml.setValue("marker:layer:x", (int)marker.layer.x);
	xml.setValue("marker:layer:y", (int)marker.layer.y);
	xml.setValue("marker:layer:width", (int)marker.layer.width);
	xml.setValue("marker:layer:height", (int)marker.layer.height);

	xml.saveFile(path);

	return;
}

/*
 * Werk marker bij.
 */
void MarkerHandler::update(Marker marker)
{
	for (int i = 0; i < markers.size(); i++)
	{
		if (markers.at(i).id == marker.id)
		{
			markers.at(i) = marker;
		}
	}

	return;
}
