#ifndef _RULES_BATIMENT_BATIMENTQUADJARDIN_HH
#define _RULES_BATIMENT_BATIMENTQUADJARDIN_HH

#include "all_includes.hh"


class BatimentQuadJardin : public Chose {
    private :
	Quad c;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuadJardin(Quad c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
