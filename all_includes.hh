#ifndef _ALL_INCLUDES_HH_
#define _ALL_INCLUDES_HH_

class Chose;

// DEBUG
#include <typeinfo>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "geometry/angle.hh"
#include "geometry/directions.hh"
#include "geometry/vertex.hh"
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
#include "rules/architecture/couleursDimensions.hh"

#include "rules/architecture/arche.hh"
#include "rules/architecture/batiment.hh"
#include "rules/architecture/quartier.hh"
#include "rules/architecture/routetrottoir.hh"
#include "rules/architecture/terrain.hh"
#include "rules/architecture/toit.hh"

#include "rules/batiment/batimentquad.hh"
#include "rules/batiment/batimentquadmaison.hh"
#include "rules/batiment/batimentquadjardin.hh"
#include "rules/batiment/batimentquadpont.hh"
#include "rules/batiment/batimentquadmaisonpont.hh"
#include "rules/batiment/batimentquadblock.hh"
#include "rules/batiment/batimentquadtoit.hh"
#include "rules/batiment/batimenttri.hh"
#include "rules/batiment/batimentquadmur.hh"
#include "rules/batiment/batimentquadfenetre.hh"

#endif
