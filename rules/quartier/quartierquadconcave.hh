#ifndef _RULES_QUARTIER_QUARTIERQUADCONCAVE_HH_
#define _RULES_QUARTIER_QUARTIERQUADCONCAVE_HH_

#include "all_includes.hh"

// QuadAngle est un quadrilatère avec un angle > 160.
class QuartierQuadConcave : public QuartierQuad {
    public :
	QuartierQuadConcave(Quad c);
	virtual bool split();
};

#endif
