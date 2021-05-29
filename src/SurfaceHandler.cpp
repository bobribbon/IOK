/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "SurfaceHandler.hpp"

/*
 * Oppervlaktes tekenen op de framebuffer.
 */
void SurfaceHandler::draw(Marker marker, bool outline)
{
	ofPushMatrix();

	// 1/1000 van de grootte.
	ofScale(0.001);
	
	// verwerk rotaties
	ofTranslate(WIDTH/ 2, HEIGHT / 2, marker.position.z);
	ofRotateXDeg(marker.surfaceRotation.x);
	ofRotateYDeg(marker.surfaceRotation.y);
	ofRotateZDeg(marker.surfaceRotation.z);
	ofTranslate(-WIDTH/ 2, -HEIGHT / 2, marker.position.z);
	
	for (int i = 0; i < MAX_SURFACES; i++)
	{
		if (surfaces[i].id != SURFACE_INACTIVE && surfaces[i].id == marker.surfaceId)
		{
			// verkrijg texture
			tempFramebuffer.begin();
			ofClear(0, 0, 0, 0);
			surfaces[i].framebuffer.getTexture().drawSubsection(0, 0, WIDTH, HEIGHT, marker.layer.x, marker.layer.y, marker.layer.width, marker.layer.height);
			tempFramebuffer.end();

			// centreer surface: deze coördinaten zijn voor het finetunen.
			marker.surfaceTopLeft.x -= WIDTH / 2;
			marker.surfaceTopLeft.y -= HEIGHT / 2;
			marker.surfaceTopRight.x += WIDTH / 2;
			marker.surfaceTopRight.y -= HEIGHT / 2;
			marker.surfaceBottomRight.x += WIDTH / 2;
			marker.surfaceBottomRight.y += HEIGHT / 2;
			marker.surfaceBottomLeft.x -= WIDTH / 2;
			marker.surfaceBottomLeft.y += HEIGHT / 2;

			// outline surfaces?
			if (outline)
			{
				ofPushStyle();
				ofSetLineWidth(5);
				ofSetColor(ofColor::yellow);
				ofNoFill();
				ofDrawLine(marker.surfaceTopLeft, marker.surfaceTopRight);
				ofDrawLine(marker.surfaceTopRight, marker.surfaceBottomRight);
				ofDrawLine(marker.surfaceBottomRight, marker.surfaceBottomLeft);
				ofDrawLine(marker.surfaceBottomLeft, marker.surfaceTopLeft);
				ofPopStyle();
			}

			tempFramebuffer.getTexture().draw(marker.surfaceTopLeft, marker.surfaceTopRight, marker.surfaceBottomRight, marker.surfaceBottomLeft);
		}
	}

	ofPopMatrix();

	return;
}

/*
 * Laad filmbestanden.
 */
void SurfaceHandler::load(string storyPath)
{
	ofxXmlSettings xml;

	// Laad films
	reset();

	if (!xml.loadFile(storyPath + "story.xml"))
	{
		ofLogError() << "[ofapp] can't open " + storyPath + "story.xml";
		return;
	}

	xml.pushTag("story");

	for (int i = 0; i < xml.getNumTags("surface") && i < MAX_SURFACES; i++)
	{
		xml.pushTag("surface", i);

		surfaces[i].id = xml.getValue("id", SURFACE_INACTIVE);
		surfaces[i].interactionLayerId = xml.getValue("interaction", LAYER_INACTIVE);

		for (int j = 0; j < xml.getNumTags("layer") && j < MAX_LAYERS; j++)
		{
			xml.pushTag("layer", j);
			surfaces[i].layers[j].id = xml.getValue("id", LAYER_INACTIVE);
			surfaces[i].layers[j].movie.load(storyPath + xml.getValue("file", ""));
			xml.popTag();
		}

		xml.popTag();
	}

	xml.popTag();

	return;
}

/*
 * Start afspelen films.
 */
void SurfaceHandler::start(void)
{
	for (int i = 0; i < MAX_SURFACES; i++)
	{
		if (surfaces[i].id != SURFACE_INACTIVE)
		{
			for (int j = 0; j < MAX_LAYERS; j++)
			{
				if (surfaces[i].layers[j].id != LAYER_INACTIVE)
				{
					surfaces[i].layers[j].movie.play();

					// geen loop voor interactielaag
					if (surfaces[i].layers[j].id == surfaces[i].interactionLayerId)
					{
						surfaces[i].layers[j].movie.setLoopState(OF_LOOP_NONE);
						surfaces[i].layers[j].movie.setPaused(true);
					}
				}
			}
		}
	}

	return;
}

/*
 * Reset oppervlakten en lagen.
 */
void SurfaceHandler::reset(void)
{
	for (int i = 0; i < MAX_SURFACES; i++)
	{
		surfaces[i].id = SURFACE_INACTIVE;
		surfaces[i].interactionLayerId = LAYER_INACTIVE;

		for (int j = 0; j < MAX_LAYERS; j++)
		{
			surfaces[i].layers[j].id = LAYER_INACTIVE;
		}
	}

	return;
}

/*
 * constructor
 */
void SurfaceHandler::setup(void)
{
	tempFramebuffer.allocate(WIDTH, HEIGHT, GL_RGBA);

	return;
}

/*
 * Speel de interactielagen.
 */
void SurfaceHandler::startInteraction(void)
{
	for (int i = 0; i < MAX_SURFACES; i++)
	{
		if (surfaces[i].id != SURFACE_INACTIVE)
		{
			for (int j = 0; j < MAX_LAYERS; j++)
			{
				if (surfaces[i].layers[j].id != LAYER_INACTIVE)
				{
					if (surfaces[i].layers[j].id == surfaces[i].interactionLayerId)
					{
						surfaces[i].layers[j].movie.play();
					}
				}
			}
		}
	}

	return;
}

/*
 * Werk oppervlaktes bij.
 */
void SurfaceHandler::update()
{
	for (int i = 0; i < MAX_SURFACES; i++)
	{
		if (surfaces[i].id != SURFACE_INACTIVE)
		{
			surfaces[i].framebuffer.begin();
			ofEnableAlphaBlending();
			ofClear(0, 0, 0, 0);

			for (int j = 0; j < MAX_LAYERS; j++)
			{
				if (surfaces[i].layers[j].id != LAYER_INACTIVE)
				{
					surfaces[i].layers[j].movie.update();
					surfaces[i].layers[j].movie.draw(0, 0, WIDTH, HEIGHT);
				}
			}

			ofDisableAlphaBlending();
			surfaces[i].framebuffer.end();
		}
	}

	return;
}