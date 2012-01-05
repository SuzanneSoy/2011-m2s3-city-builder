#ifndef _RULES_QUARTIER_QUARTIERQUADRECT_HH_
#define _RULES_QUARTIER_QUARTIERQUADRECT_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuartierQuadRect : public QuartierQuad {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierQuadRect(Quad c);
	virtual bool split();
};

#endif
