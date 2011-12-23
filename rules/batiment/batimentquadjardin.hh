#ifndef _RULES_BATIMENTJARDIN_HH
#define _RULES_BATIMENTJARDIN_HH

#include "all_includes.hh"


class BatimentQuadJardin : public Chose {
    private :
	Vertex corner[4];

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~BatimentQuadJardin();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
