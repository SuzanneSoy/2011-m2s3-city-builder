#ifndef _RULES_ETAGE_HH_
#define _RULES_ETAGE_HH_

#include "all_includes.hh"


class EtageQuad : public Chose {
    private :
	Quad c;
	Quad ch;
	QuadBool w;

    public :
	EtageQuad(Quad c, Quad ch, QuadBool _w);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
