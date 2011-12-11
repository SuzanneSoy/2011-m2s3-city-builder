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

#include "directions.hh"
#include "vertex.hh"
#include "segment.hh"
#include "triangle.hh"
#include "quad.hh"

#include "hash.hh"
#include "view.hh"

#include "rules/chose.hh"
#include "rules/batiment.hh"
#include "rules/carrefour.hh"
#include "rules/route.hh"
#include "rules/trottoirroute.hh"
#include "rules/quadrilatere.hh"
#include "rules/quadcroix.hh"
#include "rules/quadrect.hh"
#include "rules/quadherbe.hh"

#endif
