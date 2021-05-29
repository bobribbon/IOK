/*
* Interactieve OK
* Jeroen Lassche (j.lassche@bravis.nl)
*
* Fork van het project:
* Immersief, interactief operatiekwartier
* door Team Scheire, Imec en Jan Everaert
* https://github.com/imec-int/team_scheire_OK
*/

#include "SurfaceClass.hpp"

/*
 * Initialiseer oppervlakte.
 */
Surface::Surface(void)
{
	framebuffer.allocate(WIDTH, HEIGHT, GL_RGBA);

	id = SURFACE_INACTIVE;
	interactionLayerId = LAYER_INACTIVE;

	return;
}