#ifndef _RULES_QUAD_CROIX_HH_
#define _RULES_QUAD_CROIX_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuadCroix : public Quadrilatere {
private:
	static const int hrw = 250; // half road width : 2,50m.
public:
	QuadCroix(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
};


#endif
