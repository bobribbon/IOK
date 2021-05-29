/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "ofApp.hpp"

/*
 * Tekenen van markers, oppervlakten (videos), eventuele informatie, framecounter en berichten.
 */
void ofApp::draw(void)
{
	const int offsetX = 50;
	const int offsetY = 50;

	// teken markers en van daaruit surfaces
	arucoHandler.draw(&markerHandler, &surfaceHandler, mode);

	// teken informatie vector op het scherm
	for (int i = 0; i < info.size(); i++)
	{
		if (i == currentInfo)
		{
			ofDrawBitmapStringHighlight(" " + info.at(i) + " ", offsetX, offsetY + (i * 20), ofColor::blue, ofColor::yellow);
		}
		else
		{
			ofDrawBitmapStringHighlight(" " + info.at(i) + " ", offsetX, offsetY + (i * 20), ofColor::darkGray, ofColor::black);
		}
	}

	// teken framecounter
	if (mode & MODE_SHOW_FPS)
	{
			ofDrawBitmapStringHighlight("Fps: " + to_string((int)ofGetFrameRate()), ofGetWidth() - 10 * FONT_WIDTH, 2 * FONT_HEIGHT);
	}

	// teken toast message
	if (mode & MODE_SHOW_TOAST)
	{
		toast.print();
	}

	return;
}

/*
 * Verwerk keyboard input.
 */
void ofApp::keyPressed(int key)
{
	Marker marker;
	string filename;

	// help actief?
	if (mode & MODE_SHOW_HELP)
	{
		mode = mode ^ MODE_SHOW_HELP;
		return;
	}

	switch (key)
	{
	case '5':
		mode |= MODE_INTERACTION;
		surfaceHandler.startInteraction();
		interactionSound.setVolume(5);
		interactionSound.setLoop(false);
		interactionSound.play();
		break;

	case '6':
		mode ^= MODE_TRACK;
		if (mode & MODE_TRACK)
		{
			toast.set("Tracking aan");
		}
		else
		{
			toast.set("Tracking uit");
		}
		break;

	case '7':
		if (markerHandler.visibleMarkersId.size() > 0)
		{
			mode ^= MODE_EDIT;
			toast.set("Bewerken aan");
		}
		break;

	case '9':
		mode ^= MODE_MUTE;
		if (mode & MODE_MUTE)
		{
			backgroundSound.setVolume(0);
			toast.set("geluid gedempt");
		}
		else
		{
			backgroundSound.setVolume(volume);
			toast.set("geluid actief");
		}
		break;

	case OF_KEY_F1:
		volume--;
		if (volume < 0)
		{
			volume = 0;
		}
		backgroundSound.setVolume(volume);
		toast.set("volume " + to_string(volume));
		break;

	case OF_KEY_F2:
		volume++;
		if (volume > MAX_VOLUME)
		{
			volume = MAX_VOLUME;
		}
		backgroundSound.setVolume(volume);
		toast.set("volume " + to_string(volume));
		break;

	case 'f':
		mode ^= MODE_SHOW_FPS;
		break;

	case 'm':
		mode ^= MODE_SHOW_MARKERS;
		break;

	case 's':
		marker = markerHandler.get(markerHandler.selectedMarkerId);
		markerHandler.save(marker, storyPath + "markers/" + to_string(marker.id) + ".xml");
		ofLog() << "[marker] wrote " << storyPath + "markers/" << to_string(marker.id) << ".xml";
		toast.set("Marker " + to_string(marker.id) + " opgeslagen");
		break;

	case 't':
		mode = mode ^ MODE_SHOW_TOAST;
		break;

	case 'w':
		mode = mode ^ MODE_SHOW_CAMERA;
		break;

	case '-':
		currentStory--;
		selectStory();
		break;

	case '+':
		currentStory++;
		selectStory();
		break;

	case '[':
		currentMarker--;
		break;

	case ']':
		currentMarker++;
		break;

	case '?':
		mode |= MODE_SHOW_HELP;
		break;

	case OF_KEY_UP:
		if (mode & MODE_EDIT)
		{
			currentInfo--;
		}
		break;

	case OF_KEY_DOWN:
		if (mode & MODE_EDIT)
		{
			currentInfo++;
		}
		break;

	case OF_KEY_LEFT:
		if (mode & MODE_EDIT)
		{
			marker = markerHandler.get(markerHandler.selectedMarkerId);
			if (ofGetKeyPressed(OF_KEY_SHIFT))
			{
				markerHandler.edit(&marker, currentInfo, -10);
			}
			else
			{
				markerHandler.edit(&marker, currentInfo, -1);
			}
			markerHandler.update(marker);
		}
		break;

	case OF_KEY_RIGHT:
		if (mode & MODE_EDIT)
		{
			marker = markerHandler.get(markerHandler.selectedMarkerId);
			if (ofGetKeyPressed(OF_KEY_SHIFT))
			{
				markerHandler.edit(&marker, currentInfo, +10);
			}
			else
			{
				markerHandler.edit(&marker, currentInfo, +1);
			}
			markerHandler.update(marker);
		}
		break;
	}

	return;
}

/*
 * Laad de basisinstellingen.
 */
void ofApp::loadSettings(void)
{
	ofxXmlSettings xml;

	ofSetDataPathRoot("");

	xml.loadFile("settings.xml");
	dataPath = xml.getValue("datapath", "data/");
	framerate = xml.getValue("framerate", 24);

	ofLog() << "[settings] loaded";

	return;
}

/*
 * Laad geluiden in.
 */
void ofApp::loadSounds(void)
{
	ofxXmlSettings xml;

	if (xml.load(storyPath + "story.xml"))
	{
		xml.pushTag("story");

		if (xml.getValue("backgroundsound", "") != "")
		{
			backgroundSound.load(storyPath + xml.getValue("backgroundsound", ""));
			backgroundSound.setVolume(5);
			backgroundSound.setLoop(true);
			backgroundSound.play();
		}

		if (xml.getValue("interactionsound", "") != "")
		{
			interactionSound.load(storyPath + xml.getValue("interactionsound", ""));
		}

		xml.popTag();
	}

	return;
}

/*
 * Laad verhalen op basis van mappen onder /stories.
 * Geeft een vector van strings terug met de namen.
 */
vector<std::string> ofApp::loadStories(void)
{
	ofDirectory dir(dataPath + "stories/");
	vector<std::string> stories;
	std::string storiesFound;

	dir.listDir();

	for (int i = 0; i < dir.size(); i++)
	{
		if (dir.getFile(i).isDirectory())
		{
			stories.push_back(dir.getName(i));
			storiesFound += dir.getName(i) + " ";
		}
	}

	ofLog() << "[stories] path: " << to_string(stories.size()) << " stories found: " << storiesFound;

	return stories;
}

/*
 * Selecteer verhaal en laad assets.
 */
void ofApp::selectStory(void)
{
	ofxXmlSettings xml;

	if (currentStory < 0)
	{
		currentStory = 0;
	}
	if (currentStory > stories.size() - 1)
	{
		currentStory = stories.size() - 1;
	}

	// Laad markers
	markerHandler.loadMarkers(storyPath);

	// Laad films
	surfaceHandler.load(storyPath);
	surfaceHandler.start();

	// Laad geluiden
	// TODO: soundHandler.load(storyPath)?
	loadSounds();

	toast.set("[story] " + stories[currentStory] + " geladen");
	ofLog() << "[stories] loaded " << stories[currentStory];

	return;
}

/*
 * Iniatialiseer app.
 */
void ofApp::setup(void)
{
	ofLog() << "[start] " << ofGetTimestampString("%c");

	// laad appinstellingen uit map met binary
	loadSettings();

	ofSetFrameRate(framerate);
	arucoHandler.setup(dataPath);
	surfaceHandler.setup();

	mode = MODE_SHOW_CAMERA | MODE_SHOW_FPS | MODE_SHOW_TOAST | MODE_TRACK;

	//ofLogToFile("log.txt", true);
	ofLogToConsole();

	// laad vector met beschikbare verhalen en laad het eerste verhaal in
	stories = loadStories();
	selectStory();

	return;
}

/*
 * App loop.
 */
void ofApp::update(void)
{
	arucoHandler.update(mode);
	markerHandler.visibleMarkersId = arucoHandler.getVisibleMarkersIds();
	surfaceHandler.update();

	info = {};

	if (currentInfo < 0)
	{
		currentInfo = 0;
	}
	if (currentInfo > MARKER_NUM_VARIABLES)
	{
		currentInfo = MARKER_NUM_VARIABLES;
	}

	if (mode & MODE_SHOW_HELP)
	{
		currentInfo = -1;
		info.push_back("+-  : wissel story");
		info.push_back("[]  : wissel active marker");
		
		info.push_back("5   : start interactie");
		info.push_back("6   : start/stop trackingmodus");
		info.push_back("7   : start/stop marker editmodus");
		info.push_back("s   : marker instellingen opslaan");
		
		info.push_back("f   : toon/verberg fps teller");
		info.push_back("t   : toon/verberg berichten");
		info.push_back("w   : toon/verberg webcam");

		info.push_back("F1  : geluid zachter");
		info.push_back("F2  : geluid harder");
		info.push_back("9   : geluid wel/niet dempen");

		info.push_back("?   : help");		
		info.push_back("Esc : afsluiten");
	}


	if (currentMarker < 0)
	{
		currentMarker = 0;
	}
	if (currentMarker >= markerHandler.visibleMarkersId.size())
	{
		currentMarker = markerHandler.visibleMarkersId.size() - 1;
	}

	if (mode & MODE_EDIT)
	{
		if (markerHandler.visibleMarkersId.size() > 0 && currentMarker < markerHandler.visibleMarkersId.size())
		{
			markerHandler.selectedMarkerId = markerHandler.visibleMarkersId.at(currentMarker);
			Marker marker = markerHandler.get(markerHandler.selectedMarkerId);
			info = markerHandler.getInfo(marker);
		}
		else
		{
			toast.set("Geen markers gevonden");
		}
	}

	return;
}