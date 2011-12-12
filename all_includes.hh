#ifndef _ALL_INCLUDES_HH_
#define _ALL_INCLUDES_HH_

typedef long long int64;

class Chose;

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

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
#include "view.hh"

#include "rules/chose.hh"
#include "rules/batiment/batiment.hh"
#include "rules/route/carrefour.hh"
#include "rules/route/route.hh"
#include "rules/route/trottoir.hh"
#include "rules/quartier/quadrilatere.hh"
#include "rules/quartier/quadcroix.hh"
#include "rules/quartier/quadrect.hh"
#include "rules/quartier/quadangle.hh"
#include "rules/terrain/quadherbe.hh"
#include "rules/tiletri.hh"

#endif
