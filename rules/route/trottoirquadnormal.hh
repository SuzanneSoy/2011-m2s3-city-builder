#ifndef _RULES_TROTTOIRROUTE_HH_
#define _RULES_TRTTOIRROUTE_HH_

#include "all_includes.hh"

class TrottoirQuadNormal : public Chose {
	private :
	Quad c;
	int height;
	// TODO : pas besoin de ce champ : il suffit d'orienter
	// correctement le trottoir lorsqu'on le crée.
	Cardinal border;

	public :
	TrottoirQuadNormal(Quad c, int height, Cardinal border);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
