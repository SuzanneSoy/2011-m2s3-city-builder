#ifndef _RULES_ETAGE_HH_
#define _RULES_ETAGE_HH_

#include "all_includes.hh"


class EtageQuad : public Chose {
    private :
	Quad c;
	Quad ch;
	bool we, ws, ww, wn;

    public :
	EtageQuad(Quad c, Quad ch, bool we=true, bool ws=true, bool ww=true, bool wn=true);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
