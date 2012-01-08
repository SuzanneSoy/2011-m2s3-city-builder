#ifndef _RULES_QUARTIER_QUARTIERTRITRAPEZE_HH_
#define _RULES_QUARTIER_QUARTIERTRITRAPEZE_HH_

#include "all_includes.hh"

class QuartierTriTrapeze : public QuartierTri {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierTriTrapeze(Triangle c);
	virtual bool split();
};

#endif
