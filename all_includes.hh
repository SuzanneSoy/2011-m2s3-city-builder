#ifndef _ALL_INCLUDES_HH_
#define _ALL_INCLUDES_HH_

class Chose;

// DEBUG
#include <typeinfo>

#include <iostream>
#include <iomanip> // DEBUG
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

// Affichage du FPS
#include <GL/freeglut.h>
//#include <openglut.h>
#include <stdio.h>


#include "geometry/directions.hh"
#include "geometry/vertex.hh"
#include "geometry/angle.hh"
#include "geometry/segment.hh"
#include "geometry/triangle.hh"
#include "geometry/quad.hh"

#include "gputriangle.hh"
#include "hash.hh"
// heap.hh must be included before lod.hh
#include "heap.hh"
// lod.hh must be included before chose.hh and view.hh
#include "lod.hh"
#include "view.hh"

#include "rules/chose.hh"
#include "rules/couleursDimensions.hh"

#include "rules/arbre.hh"
#include "rules/arche.hh"
#include "rules/batiment.hh"
#include "rules/quartier.hh"
#include "rules/routetrottoir.hh"
#include "rules/terrain.hh"
#include "rules/toit.hh"
#include "rules/etage.hh"
#include "rules/mur.hh"

#endif
