#ifndef _RULES_QUARTIER_QUARTIERTRIORTHOCENTRE_HH_
#define _RULES_QUARTIER_QUARTIERTRIORTHOCENTRE_HH_

#include "all_includes.hh"

class QuartierTriCentre : public QuartierTri {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierTriCentre(Triangle c);
	virtual bool split();
};

#endif
