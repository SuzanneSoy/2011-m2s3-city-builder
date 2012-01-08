#ifndef _RULES_QUARTIER_QUARTIERQUADANGLE_HH_
#define _RULES_QUARTIER_QUARTIERQUADANGLE_HH_

#include "all_includes.hh"

// QuadAngle est un quadrilatère avec des angles malfichus (< 90-40 ou > 90+40).
class QuartierQuadAngle : public QuartierQuad {
    private :
	static const int hrw = 150; // half road width : 1,50m.

    public :
	QuartierQuadAngle(Quad c);
	virtual bool split();
};

#endif
