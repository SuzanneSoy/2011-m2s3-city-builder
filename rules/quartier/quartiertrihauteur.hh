#ifndef _RULES_QUARTIER_TRI_HAUTEUR_HH_
#define _RULES_QUARTIER_TRI_HAUTEUR_HH_

#include "all_includes.hh"

class QuartierTriHauteur : public QuartierTri {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierTriHauteur(Vertex left, Vertex top, Vertex right);
	virtual bool split();
};

#endif
