#ifndef _RULES_QUAD_HERBE_HH_
#define _RULES_QUAD_HERBE_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuadHerbe : public Quadrilatere {
private:
	int red;
public:
	QuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	QuadHerbe(int red, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void triangulation();
};


#endif
