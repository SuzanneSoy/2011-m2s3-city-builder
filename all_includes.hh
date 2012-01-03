#ifndef _ALL_INCLUDES_HH_
#define _ALL_INCLUDES_HH_

typedef long long int64;

class Chose;

// DEBUG
#include <typeinfo>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "angle.hh"
#include "directions.hh"
#include "vertex.hh"
#include "segment.hh"
#include "triangle.hh"
#include "quad.hh"

#include "hash.hh"
// heap.hh must be included before lod.hh
#include "heap.hh"
// lod.hh must be included before chose.hh and view.hh
#include "lod.hh"
#include "view.hh"

#include "rules/chose.hh"

#include "rules/batiment/batimentquad.hh"
#include "rules/batiment/batimentquadmaison.hh"
#include "rules/batiment/batimentquadjardin.hh"
#include "rules/batiment/batimentquadpont.hh"
#include "rules/batiment/batimentquadmaisonpont.hh"
#include "rules/batiment/batimentquadblock.hh"
#include "rules/batiment/batimentquadtoit.hh"

#include "rules/quartier/quartierquad.hh"
#include "rules/quartier/quartierquadangle.hh"
#include "rules/quartier/quartierquadcarre.hh"
#include "rules/quartier/quartierquadrect.hh"
#include "rules/quartier/quartiertri.hh"

#include "rules/route/routequadcarrefour.hh"
#include "rules/route/routequadchaussee.hh"
#include "rules/route/routetrichaussee.hh"

#include "rules/route/trottoirquadnormal.hh"

#include "rules/terrain/terrainquadherbe.hh"

#endif
