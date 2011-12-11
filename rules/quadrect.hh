#ifndef _RULES_QUAD_RECT_HH_
#define _RULES_QUAD_RECT_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuadRect : public Quadrilatere {
private:
	static const int hrw = 250; // half road width : 2,50m.
public:
	QuadRect(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
};

#endif
