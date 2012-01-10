#ifndef _RULES_QUARTIER_QUARTIERQUADANGLE_HH_
#define _RULES_QUARTIER_QUARTIERQUADANGLE_HH_

#include "all_includes.hh"

// QuadAngle est un quadrilatère avec des angles malfichus (< 90-40 ou > 90+40).
class QuartierQuadAngle : public QuartierQuad {
    public :
	QuartierQuadAngle(Quad c);
	virtual bool split();
};

#endif
